

/*
Kernel.c
Build Date  : 16-12-2024
Last Update : 15-01-2025
Description : KeblaOS is a x86 architecture based 64 bit Operating System. Currently it is using Limine Bootloader.
Reference   : https://wiki.osdev.org/Limine
              https://github.com/limine-bootloader/limine-c-template
              https://wiki.osdev.org/Limine_Bare_Bones

*/

#include "../process/process.h" 
// #include "../pcb/task.h"

#include "../bootloader/acpi.h" // init_acpi
#include "../x86_64/interrupt/apic.h"
#include "../x86_64/interrupt/pic.h" // init_idt, test_interrupt
#include "../bootloader/ahci.h"
#include "../bootloader/pci.h"
#include "../bootloader/disk.h"
#include "../bootloader/cpu.h"
#include "../bootloader/memory.h"
#include "../bootloader/firmware.h"

#include "../limine/limine.h" // bootloader info
#include "../bootloader/boot.h" // bootloader info
#include "../lib/stdio.h" // printf
#include "../util/util.h" // registers_t , halt_kernel

#include "../driver/vga/framebuffer.h"
#include "../driver/vga/vga_term.h" // vga_init, print_bootloader_info, print_memory_map, display_image
#include "../driver/image_data.h"

#include "../driver/io/serial.h"

#include "../x86_64/gdt/gdt.h" // init_gdt

#include "../mmu/pmm.h" // init_pmm, test_pmm
#include "../mmu/paging.h" // init_paging, test_paging
#include "../mmu/kmalloc.h" // test_kmalloc
#include "../mmu/vmm.h" // test_vmm
#include "../mmu/kheap.h" // init_kheap, test_kheap
#include "../driver/keyboard/keyboard.h" // initKeyboard
#include "../x86_64/timer/pic_timer.h" // init_timer
#include "../x86_64/timer/apic_timer.h"

#include "../usr/shell.h"


#include "kernel.h"



void kmain(){
    serial_init();
    get_bootloader_info();
    get_memory_info();
    vga_init();

    printf("%s - %s\n", OS_NAME, OS_VERSION);

    init_gdt();

    if(has_apic() == 1){
        init_apic_interrupt();
        init_apic_timer();
    }else{
        init_pic_interrupt();
        init_pic_timer(1);
    }
    
    initKeyboard();

    init_pmm();
    init_paging();
    init_kheap();
    
    init_acpi();

    // detect_ahci();
    // init_ahci( 0xFEBD5000);
    // pci_scan();
    // get_disk_info();


    init_processes();
    
    halt_kernel();
}













