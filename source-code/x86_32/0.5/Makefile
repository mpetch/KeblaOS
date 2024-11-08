#Automated Building Process

SRC_DIR = src
BOOTLOADER_SRC_DIR = $(SRC_DIR)/bootloader
DRIVER_SRC_DIR = $(SRC_DIR)/driver
KERNEL_SRC_DIR = $(SRC_DIR)/kernel
STDLIB_SRC_DIR = $(SRC_DIR)/stdlib
GDT_SRC_DIR = $(SRC_DIR)/gdt
IDT_SRC_DIR = $(SRC_DIR)/idt
UTL_SRC_DIR = $(SRC_DIR)/utl

BUILD_DIR = build

ISO_DIR = iso

OS_NAME = KeblaOS
VERSION = 0.5

HOME = /home/baponkar


GCC = $(HOME)/opt/cross/bin/i686-elf-gcc
GCC_FLAG = -ffreestanding -Wall -Wextra -g -O2
LD = $(HOME)/opt/cross/bin/i686-elf-ld

NASM = nasm
NASM_FLAG = -f elf32

default: run



########################## BootLoader START ########################################

# Generating boot.o
$(BUILD_DIR)/boot.o: $(BOOTLOADER_SRC_DIR)/boot.s
	$(NASM) $(NASM_FLAG) $(BOOTLOADER_SRC_DIR)/boot.s -o $(BUILD_DIR)/boot.o

########################## BootLoader EEND #########################################



############################ GDT Build Start #######################################
# Generating gdt_s.o
$(BUILD_DIR)/gdt_s.o: $(GDT_SRC_DIR)/gdt.s
	$(NASM) $(NASM_FLAG) $(GDT_SRC_DIR)/gdt.s -o $(BUILD_DIR)/gdt_s.o

# Generating gdt.o
$(BUILD_DIR)/gdt.o: $(GDT_SRC_DIR)/gdt.c
	$(GCC) $(GCC_FLAG) -c $(GDT_SRC_DIR)/gdt.c -o $(BUILD_DIR)/gdt.o

############################ GDT End ###############################################




############################ IDT Build Start #######################################
# Generating gdt_s.o
$(BUILD_DIR)/idt_s.o: $(IDT_SRC_DIR)/idt.s
	$(NASM) $(NASM_FLAG) $(IDT_SRC_DIR)/idt.s -o $(BUILD_DIR)/idt_s.o

# Generating gdt.o
$(BUILD_DIR)/idt.o: $(IDT_SRC_DIR)/idt.c
	$(GCC) $(GCC_FLAG) -c $(IDT_SRC_DIR)/idt.c -o $(BUILD_DIR)/idt.o


# Generating timer.o
$(BUILD_DIR)/timer.o: $(IDT_SRC_DIR)/timer.c
	$(GCC) $(GCC_FLAG) -c $(IDT_SRC_DIR)/timer.c -o $(BUILD_DIR)/timer.o

############################ IDT End ###############################################



############################ DRIVER Build START ######################################

# Generating ports.o
$(BUILD_DIR)/ports.o: $(DRIVER_SRC_DIR)/ports.c
	$(GCC) $(GCC_FLAG) -c $(DRIVER_SRC_DIR)/ports.c -o $(BUILD_DIR)/ports.o


# Generating vga.o
$(BUILD_DIR)/vga.o: $(DRIVER_SRC_DIR)/vga.c
	$(GCC) $(GCC_FLAG) -c $(DRIVER_SRC_DIR)/vga.c -o $(BUILD_DIR)/vga.o

############################ DRIVER Build END ########################################




######################### Utl START ################################################

# Generating kernel.o
$(BUILD_DIR)/utl.o: $(UTL_SRC_DIR)/utl.c
	$(GCC) $(GCC_FLAG) -c $(UTL_SRC_DIR)/utl.c -o $(BUILD_DIR)/utl.o

######################### Utl END ###################################################




######################### Kernel START ################################################

# Generating kernel.o
$(BUILD_DIR)/kernel.o: $(KERNEL_SRC_DIR)/kernel.c
	$(GCC) $(GCC_FLAG) -c $(KERNEL_SRC_DIR)/kernel.c -o $(BUILD_DIR)/kernel.o

######################### Kernel END ###################################################



############################# Building ISO image file START ############################

# Generating kernel.bin file
$(BUILD_DIR)/kernel.bin: $(BUILD_DIR)/kernel.o \
						$(SRC_DIR)/linker.ld  \
						$(BUILD_DIR)/boot.o  \
						$(BUILD_DIR)/ports.o \
						$(BUILD_DIR)/vga.o \
						$(BUILD_DIR)/gdt_s.o \
						$(BUILD_DIR)/gdt.o \
						$(BUILD_DIR)/idt_s.o \
						$(BUILD_DIR)/idt.o \
						$(BUILD_DIR)/utl.o \
						$(BUILD_DIR)/timer.o

	# Linking all object file
	$(LD) -m elf_i386 -T $(SRC_DIR)/linker.ld -o $(BUILD_DIR)/kernel.bin \
						$(BUILD_DIR)/kernel.o  \
						$(BUILD_DIR)/boot.o  \
						$(BUILD_DIR)/ports.o \
						$(BUILD_DIR)/vga.o \
						$(BUILD_DIR)/gdt_s.o \
						$(BUILD_DIR)/gdt.o \
						$(BUILD_DIR)/idt_s.o \
						$(BUILD_DIR)/idt.o \
						$(BUILD_DIR)/utl.o \
						$(BUILD_DIR)/timer.o

	# Automatic cleaning object files	
	make clean

#Building ISO image
$(BUILD_DIR)/$(OS_NAME).iso: $(BUILD_DIR)/kernel.bin $(BOOTLOADER_SRC_DIR)/grub.cfg
	mkdir -p build
	mkdir -p iso/boot/grub
	cp $(BOOTLOADER_SRC_DIR)/grub.cfg iso/boot/grub/grub.cfg 	#Copy grub.cfg file 
	cp $(BUILD_DIR)/kernel.bin iso/boot/kernel.bin	#Copy kernel.bin file
	grub-mkrescue -o $(BUILD_DIR)/$(OS_NAME).iso iso		#Creating ISO image 

############################# Building ISO image file END ###########################


clean:
	rm -f $(BUILD_DIR)/*.o


build: $(BUILD_DIR)/$(OS_NAME).iso

run: $(BUILD_DIR)/$(OS_NAME).iso
	qemu-system-i386 -cdrom $(BUILD_DIR)/$(OS_NAME).iso -serial file:serial_output.log -d guest_errors,int -D qemu.log -soundhw pcspk

help:
	@echo "Available targets:"
	@echo "  make run             - Run the default target (displays this help message)"
	@echo "  make build           - Compile the project (simulated in this example)"
	@echo "  make clean           - Clean up build artifacts"
	@echo "  make help            - Display this help menu"


# The process can be implemented by make along with the default, build,run  and clean
.PHONY: default build run clean help
