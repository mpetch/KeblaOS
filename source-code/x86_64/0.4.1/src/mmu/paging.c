
#include "paging.h"

extern uint64_t *frames;
extern uint64_t nframes;

extern uint64_t placement_address; // The value of it will set in kernel.c 
extern uint64_t mem_end_address;    // The value of it will set in kernel.c 


page_directory_t * current_directory;
page_directory_t * kernel_directory;

// Function to allocate a frame.
void alloc_frame(page_t *page, int is_kernel, int is_writeable)
{
   if (page->frame != 0)
   {
       return; // Frame was already allocated, return straight away.
   }
   else
   {
       uint64_t idx = first_frame(); // idx is now the index of the first free frame.
       if (idx == (uint64_t)-1)
       {
           // PANIC is just a macro that prints a message to the screen then hits an infinite loop.
           print("No free frames!");
       }
       set_frame(idx*0x1000); // this frame is now ours!
       page->present = 1; // Mark it as present.
       page->rw = (is_writeable)?1:0; // Should the page be writeable?
       page->user = (is_kernel)?0:1; // Should the page be user-mode?
       page->frame = idx;
   }
}

// Function to deallocate a frame.
void free_frame(page_t *page)
{
   uint64_t frame;
   if (!(frame=page->frame))
   {
       return; // The given page didn't actually have an allocated frame!
   }
   else
   {
       clear_frame(frame); // Frame is now free again.
       page->frame = 0x0; // Page now doesn't have a frame.
   }
}



void initialise_paging()
{
    
    nframes = mem_end_address / 0x1000;
    frames = (uint64_t *)kmalloc(INDEX_FROM_BIT(nframes));
    memset(frames, 0, INDEX_FROM_BIT(nframes));

    // Allocate and zero-initialize the PML4 table
    kernel_directory = (page_directory_t *) kmalloc_a(sizeof(page_directory_t), 1);
    memset(kernel_directory, 0, sizeof(page_directory_t));
    current_directory = kernel_directory;

    // Identity-map the physical memory up to `placement_address`
    int total_pages = 0;
    for (uint64_t i = placement_address; i< mem_end_address; i += 0x1000)
    {
        print("\nPhysical address : ");
        print_hex(i);
        print("\n");
        // Kernel code is readable but not writeable from user space
        alloc_frame(get_page(i, 1, kernel_directory), 0, 0);
        total_pages++;
    }
    
    print("Kernel Directory pointer :");
    print_hex((uint64_t) kernel_directory);
    print("\n");
    // switch_page_directory(kernel_directory);  // Enable paging
}


void switch_page_directory(page_directory_t *dir)
{
    current_directory = dir;
    asm volatile("mov %0, %%cr3" ::"r"(dir->physicalAddr));
    uint64_t cr0;
    asm volatile("mov %%cr0, %0" : "=r"(cr0));
    cr0 |= 0x80000000; // Enable paging
    asm volatile("mov %0, %%cr0" ::"r"(cr0));
}

/*
here address means virtual address as well as physical address as we are using identity map.
*/
page_t *get_page(uint64_t address, int make, page_directory_t *dir)
{
    // Extract indices for PML4, PDPT, PD, and PT from virtual address
    uint64_t pml4_index = (address >> 39) & 0x1FF;
    uint64_t pdpt_index = (address >> 30) & 0x1FF;
    uint64_t pd_index = (address >> 21) & 0x1FF;
    uint64_t pt_index = (address >> 12) & 0x1FF;

    print("Virtual Address : ");
    print_hex(address);
    print("\n");

    print("pml4_index : ");
    print_dec(pml4_index);
    print("\n");

    print("pdpt_index : ");
    print_dec(pdpt_index);
    print("\n");

    print("pd_index : ");
    print_dec(pd_index);
    print("\n");

    print("pt_index : ");
    print_dec(pt_index);
    print("\n");

    // PML4 => PDPT => PT => Page
    // PML4 has a table with 512 entries of pdpt
    // Each PDPT has 512 entries of PT
    // Each PT has 512 entries of Pages
    // Get or create the PDPT
    if (!dir->tables[pml4_index]) // Check following pml4 index 
    {
        if (!make)
            return 0;
        uint64_t tmp;
        dir->tables[pml4_index] = (page_table_t *) kmalloc_ap(sizeof(page_table_t), 1, &tmp); // Create page_table_t on the base &tmp
        memset(dir->tables[pml4_index], 0, sizeof(page_table_t));   // 64 zeros
        dir->physicalAddr = tmp; // Storing its physical address

        print("Physical Address of PML4 in PML4: ");
        print_hex(dir->physicalAddr);
        print("\n");

        
        print("Physical address of pdpt table in PML4: ");
        print_hex(dir->physicalAddr & 0xFFFFFFFFFF000);
        print("\n");
    }

    page_table_t *pdpt = dir->tables[pml4_index];
    if (!pdpt->pages[pdpt_index].present)
    {
        if (!make)
            return 0;
        uint64_t tmp;
        pdpt->pages[pdpt_index] = (page_t){.present = 1, .rw = 1, .frame = tmp >> 12};
        print("Physical Address of PD in PDPT Page Directory: ");
        print_hex(pdpt->pages[pdpt_index].frame);
        print("\n");
    }

    // Get or create the PD
    page_table_t *pd = (page_table_t *)(pdpt->pages[pdpt_index].frame << 12);
    if (!pd->pages[pd_index].present)
    {
        if (!make)
            return 0;
        uint64_t tmp;
        pd->pages[pd_index] = (page_t){.present = 1, .rw = 1, .frame = tmp >> 12};
        print("Physical Address of PT in Page Directory: ");
        print_hex( pd->pages[pd_index].frame);
        print("\n");
    }

    // Get or create the PT
    page_table_t *pt = (page_table_t *)(pd->pages[pd_index].frame << 12);
    if (!pt->pages[pt_index].present)
    {
        if (!make)
            return 0;
        uint64_t tmp;
        pt->pages[pt_index] = (page_t){.present = 1, .rw = 1, .frame = tmp >> 12};
        print("Physical Address Page in Page Table: ");
        print_hex(pt->pages[pt_index].frame);
        print("\n");
    }

    print("Physical Address of Page: ");
    print_hex((uint64_t) &pt->pages[pt_index]);
    print("\n");

    return &pt->pages[pt_index];
} 

void page_fault_handler(registers_t *regs)
{
    // A page fault has occurred.
    // Retrieve the faulting address from the CR2 register.
    uint64_t faulting_address;
    asm volatile("mov %%cr2, %0" : "=r"(faulting_address));

    // Decode the error code to determine the cause of the page fault.
    int present = !(regs->err_code & 0x1); // Page not present
    int rw = regs->err_code & 0x2;         // Write operation?
    int us = regs->err_code & 0x4;         // Processor was in user mode?
    int reserved = regs->err_code & 0x8;   // Overwritten CPU-reserved bits of page entry?
    int id = regs->err_code & 0x10;        // Caused by an instruction fetch?

    // Output an error message with details about the page fault.
    print("Page fault! ( ");
    if (present) print("not present ");
    if (rw) print("write ");
    if (us) print("user-mode ");
    if (reserved) print("reserved ");
    if (id) print("instruction fetch ");
    print(") at address ");
    print_hex(faulting_address);
    print("\n");


    // Additional action to handle the page fault could be added here,
    // such as invoking a page allocator or terminating a faulty process.

    // Halt the system to prevent further errors (for now).
    print("Halting the system due to page fault.\n");
    asm volatile("hlt");

}




void test_paging(){
    uint64_t* test_address = (uint64_t*)0xFFFFFFFF80000000;  // Higher-half virtual address
    *test_address = 0x12345678ABCDEF00;

    uint64_t* invalid_address = (uint64_t*)0xFFFFFFFF90000000;  // Unmapped address
    *invalid_address = 0x0;  // This should trigger a page fault
}