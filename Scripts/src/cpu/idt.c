#include <stdint.h>
#include "idt.h"

static IDT_ENTRY IDT_TABLE[IDT_MAX_DESCRIPTORS];

static IDTR IDTR_P = 
{
  sizeof(IDT_TABLE)-1,
  IDT_TABLE //due to pointer decay its equivalent to &IDT_TABLE[0]
};

void IDT_SET_GATE(uint8_t interrupt, uint16_t BaseLow, uint8_t segment_selector, uint8_t attributes, uint16_t BaseHigh)
{
  IDT_TABLE[interrupt].BaseLow = BaseLow;
  IDT_TABLE[interrupt].segment_selector = segment_selector;
  IDT_TABLE[interrupt].attributes = attributes;
  IDT_TABLE[interrupt].reserved = 0; //Always 0
  IDT_TABLE[interrupt].BaseHigh = BaseHigh;
}

static inline void IDT_GATE_ENABLE(uint8_t interrupt)
{
  IDT_TABLE[interrupt].attributes |= 0x80;
}

static inline void IDT_GATE_DISABLE(uint8_t interrupt)
{
  IDT_TABLE[interrupt].attributes &= ~0x80;
}

void INITIALIZE_IDT()
{
  LOAD_IDT(&IDTR_P);
}