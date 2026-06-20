#pragma once
#include <stdint.h>

#define IDT_MAX_DESCRIPTORS       256
#define IDT_MAX_CPU_EXCEPTIONS    32

typedef struct 
{
  uint16_t BaseLow;
  uint16_t segment_selector;
  uint8_t reserved;
  uint8_t attributes;
  uint16_t BaseHigh;

}__attribute__((packed)) IDT_ENTRY;


typedef struct
{
  uint16_t size;
  IDT_ENTRY* base;

}__attribute__((packed)) IDTR;

extern void __attribute__((cdecl)) LOAD_IDT (IDTR* IDTR_P);


typedef enum
{

//The flags are from bit 48-40 defined as a single uint8_t

//40-43 is gate type(4 bit value)
//46-45 DPL (2 bit value)
//47 Present Bit(1 bit value)

//Hence these specific values and for the descriptor to be valid the last bit P should be 1
//Therefore we used 0x80 here, or you can do 1<<7 to get it to 8th bit

  //GATE TYPE
  IDT_FLAG_TASK_GATE                    =0x05,
  IDT_FLAG_INTERRUPT_GATE_16BIT         =0x06,
  IDT_FLAG_INTERRUPT_GATE_32BIT         =0x0E,
  IDT_FLAG_TRAP_GATE_16BIT              =0x07,
  IDT_FLAG_TRAO_GATE_32BIT              =0x0F,

  //PRESENT BIT
  IDT_FLAG_PRESENT                      =0x80,
  
  //DPL FLAGS
  IDT_FLAG_DPL_0                        =(0 << 5), //KERNEL
  IDT_FLAG_DPL_1                        =(1 << 5),
  IDT_FLAG_DPL_2                        =(2 << 5),
  IDT_FLAG_DPL_3                        =(3 << 5)
} IDT_FLAGS;


void IDT_SET_GATE(uint8_t interrupt, uint16_t BaseLow, uint8_t segment_selector, uint8_t attributes, uint16_t BaseHigh);
void INITIALIZE_IDT();

void IDT_GATE_ENABLE(uint8_t interrupt);
void IDT_GATE_DISABLE(uint8_t interrupt);

