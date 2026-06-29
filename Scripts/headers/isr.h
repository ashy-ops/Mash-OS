#pragma once
#include <stdint.h>

typedef struct {
    uint32_t ds;                                          // Pushed by us
    uint32_t edi, esi, ebp, esp_ignored, ebx, edx, ecx, eax; // Pushed by pusha,eax pushed by us
    uint32_t interrupt;                                   // Pushed by macro
    uint32_t error;                                       // Pushed by macro
    uint32_t eip, cs, eflags;                             // Pushed by CPU
} __attribute__((packed)) registers_t;

typedef void (*isr_handler_t)(registers_t* regs);    //function pointer with regs as argument
//passing the struct as pointer for efficiency!


void isr_initialize(void);
void isr_register_handler(int interrupt, isr_handler_t handler);
void default_handler(registers_t* regs);
void __attribute((cdecl)) isr_handler(registers_t* regs); //called by the assembly code
