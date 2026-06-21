#include <stdint.h>
#include "pic.h"
#include "idt.h"
#include "display.h"

volatile char* VGA_BUFFER = (volatile char*)0xB8000;

void kernel_main()
{
  pic_remap();
  INITIALIZE_IDT(); 
  terminal_initialize();
  write_to_terminal("Hello From the OS! but in RED :)",RED); 
  write_to_terminal("Hello my name is %s and my age is %i!",BLACK,"Sehaj",25);

  while(1)
  {
    
  }
}