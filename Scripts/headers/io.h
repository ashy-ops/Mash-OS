#pragma once
#include <stdint.h>

extern void __attribute__((cdecl)) outb(uint16_t port,uint8_t value);
extern uint8_t __attribute__((cdecl)) inb(uint16_t port);
extern void __attribute__((cdecl)) io_wait();
