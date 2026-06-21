#include "idt.h"
#include "isr.h"
#include "io.h"
#include "isr_setup.h"
#include "display.h"


ISRHandler handlers[256];     //function pointer table

void ISR_Initialize()
{
  ISR_INITIALIZE_GATES();
  for(int i =0; i<256; i++)
  {
    IDT_GATE_ENABLE(i);
  }

}
void __attribute((cdecl)) ISR_HANDLER(Registers* regs)
{
  uint8_t n = regs->interrupt;

  if(n>=32 && n <48)
  {
    outb(0x20,0x20);
    if(n>=40)
    {
      outb(0xA0,0x20);
    }
  }

}
