#pragma once

#include "../driver/vga.h"
#include "../stdlib/stdint.h"
#include "../util/util.h"


void syscall_handler(registers_t *regs);
int sys_write(const char *str);