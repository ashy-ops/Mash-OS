#pragma once
#include <stdint.h>

typedef struct {
    uint32_t ds;                                          // Pushed by us
    uint32_t edi, esi, ebp, esp_ignored, ebx, edx, ecx, eax; // Pushed by pusha
    uint32_t interrupt;                                   // Pushed by macro
    uint32_t error;                                       // Pushed by macro
    uint32_t eip, cs, eflags;                             // Pushed by CPU
} __attribute__((packed)) Registers;

typedef void (*ISRHandler)(Registers* regs);    //function pointer with regs as argument

void ISR_Initialize();
void _ISR_RegisterHandler(int interrupt, ISRHandler handler);
