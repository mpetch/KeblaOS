
#include "shell.h"

bool shell_running = false;  // Global flag to manage shell state

void shell_prompt() {
    print("KeblaOS>> ");
}


void execute_command(char* command) {
    
    if (strcmp(command, "help") == 0) {
        print("Available commands:\n [ help, clear, reboot, poweroff, bootinfo,");
        print("time, uptime, regvalue, checkgdt, features, testint, logo, image,");
        print("memmap,  exit,\n\t kermod, rsdp, firmware, stack, limine, pagingmod," );
        print("phystoviroff, smp, hhdm ]\n");
    } else if (strcmp(command, "clear") == 0) {
        clear_screen();  // Clear the screen using your VGA driver
    } else if (strcmp(command, "reboot") == 0) {
        print("Rebooting...\n");
        qemu_reboot();
    } else if (strcmp(command, "poweroff") == 0){
        print("Shutting Down!\n");
        print("Please Wait...");
        qemu_poweroff();
    } else if(strcmp(command, "bootinfo") == 0){
        print_bootloader_info();
    } else if (strcmp(command, "time") == 0){
        // print_current_time();
        // printing current time
    } else if (strcmp(command, "uptime") == 0){
        print("Up time : \n");
        // printing the time run this os
    }else if (strcmp(command, "regvalue") == 0){
        // print_registers();
    }else if (strcmp(command, "checkgdt") == 0){
        check_gdt();
    }else if (strcmp(command, "features") == 0){
        print_features();
    }else if (strcmp(command, "testint") == 0){
        print("Test Interrupts\n");
        test_interrupt();
    }else if (strcmp(command, "exit") == 0) {
        print("Exiting shell...\n");
        shell_running = false;
    }else if(strcmp(command, "logo") == 0){
        clear_screen();
        display_image(0, 0, (const uint64_t*) KeblaOS_icon_320x200x32, KEBLAOS_ICON_320X200X32_WIDTH,KEBLAOS_ICON_320X200X32_HEIGHT);
    }else if(strcmp(command, "image") == 0){
        clear_screen();
        display_image(0, 0, (const uint64_t*) girl_6352783_640, GIRL_6352783_640_WIDTH, GIRL_6352783_640_HEIGHT);
    }else if(strcmp(command, "") == 0){
        print("type 'help'\n");
    }else if(strcmp(command, "memmap") == 0){
        print_memory_map();
    }else if(strcmp(command, "kermod") == 0){
        print_kernel_modules_info();
    }else if(strcmp(command, "rsdp") == 0){
        print_rsdp_info();
    }else if(strcmp(command, "firmware") == 0){
        print_firmware_info();
    }else if(strcmp(command, "stack") == 0){
        print_stack_info();
    }else if(strcmp(command, "limine") == 0){
        print_limine_info();
    }else if(strcmp(command, "pagingmod") == 0){
        print_paging_mode_info();
    }else if(strcmp(command, "phystoviroff") == 0){
        print_kernel_to_virtual_offset();
    }else if(strcmp(command, "smp") == 0){
        print_smp_info();
    }else if(strcmp(command, "hhdm") == 0){
        print_hhdm_info();
    }else{
        print("!Unknown command: ");
        print(command);
        print("\n");
        print("type 'help'\n");
    }
}


void run_shell(bool is_shell_running) {
    char input[BUFFER_SIZE];

    while (is_shell_running) {
        shell_prompt();  // Display shell prompt
        //read_command(input);  // Function to read user input (can be implemented based on your keyboard handler)
        //execute_command(input);  // Process the input command
    }
}



// This C function will print the register values passed via the stack.
void print_registers_c(uint64_t rdi, uint64_t rsi, uint64_t rbp, uint64_t rsp, 
                       uint64_t rbx, uint64_t rdx, uint64_t rcx, uint64_t rax,
                       uint64_t r8,  uint64_t r9,  uint64_t r10, uint64_t r11, 
                       uint64_t r12, uint64_t r13, uint64_t r14, uint64_t r15 ) {
    print("Register Values:\n");
    
    print("RAX: ");
    print_hex(rax);
    print("\n");

    print("RBX: ");
    print_hex(rbx);
    print("\n");

    print("RCX: ");
    print_hex(rcx);
    print("\n");

    print("RDX: ");
    print_hex(rdx);
    print("\n");

    print("RSI: ");
    print_hex(rsi);
    print("\n");

    print("RDI: ");
    print_hex(rdi);
    print("\n");

    print("RBP: ");
    print_hex(rbp);
    print("\n");

    print("R8: ");
    print_hex(r8);
    print("\n");

    print("R9: ");
    print_hex(r9);
    print("\n");

    print("R10: ");
    print_hex(r10);
    print("\n");

    print("R11: ");
    print_hex(r11);
    print("\n");

    print("R12: ");
    print_hex(r12);
    print("\n");

    print("R13: ");
    print_hex(r13);
    print("\n");

    print("R14: ");
    print_hex(r14);
    print("\n");

    print("R15: ");
    print_hex(r15);
    print("\n");
}


void print_features(){
    print("KeblaOS-0.11\n");
    print("Architecture : x86_64.\n");
    print("1. Limine Bootloading.\n");
    print("2. GDT initialization.\n");
    print("3. VGA Graphics Driver.\n");
    print("4. IDT initialization.\n");
    print("5. Keyboard driver initialization.\n");
    print("6. PIT Timer initialization.\n");
    print("7. Basic User Shell\n");
    print("8. Memory Management Unit(Kheap, PMM, 4 Level Paging)\n");
    print("7. Standard Libraries : math.h, stddef.h, stdint.h, stdio.h, stdlib.h, string.h\n");
}


