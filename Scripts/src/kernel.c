#include <stdint.h>
#include "pic.h"
#include "idt.h"
#include "display.h"

#define ENTRY_COUNT 0x90000
#define MEMORMY_MAP 0x90000


volatile char* VGA_BUFFER = (volatile char*)0xB8000;

typedef struct __attribute__((packed)) {
    uint64_t baseAddress;
    uint64_t length;
    uint32_t type;
    uint32_t acpi; // ACPI 3.0 extended attributes
} MemoryMapEntry;
//uint8_t count = *(uint8_t*)ENTRY_COUNT; Throws error

void kernel_main()
{
  
  pic_remap();
  INITIALIZE_IDT(); 
  terminal_initialize();
  write_to_terminal("----------------------------------------------",WHITE);
  write_to_terminal("Displaying Memory Info: ",WHITE);
  write_to_terminal("----------------------------------------------",WHITE);


  uint8_t count = *(uint8_t*)ENTRY_COUNT;
  MemoryMapEntry* mem = (MemoryMapEntry*)MEMORMY_MAP;

  write_to_terminal("Entry Count is:%i",WHITE,count);
  write_to_terminal("Struct size is:%i",WHITE,sizeof(MemoryMapEntry));
  for(int i=0;i<6;i++)
  {
  
    uint64_t ba = mem[i].baseAddress;
    uint64_t len = mem[i].length;
    uint32_t type = mem[i].type;
    uint32_t acpi = mem[i].acpi;
    uint64_t *strt_adr = &mem[i].baseAddress;

    write_to_terminal("Base:%h, Length:%h, Type:%i,ACPI:%i",WHITE,ba,len,type,acpi,strt_adr);

    write_to_terminal("Start Addr: %h",WHITE,&mem[i].baseAddress);
  }
  write_to_terminal("----------------------------------------------",WHITE);

  while(1)
  {
    
  }
}