#include <stdint.h>
#include "pic.h"
#include "idt.h"

volatile char* VGA_BUFFER = (volatile char*)0xB8000;

void kernel_main()
{
  pic_remap();
  INITIALIZE_IDT();  
  while(1)
  {
    
  }
}