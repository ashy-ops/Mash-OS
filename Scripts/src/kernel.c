#include <stdint.h>
#include "pic.h"
#include "idt.h"
#include "display.h"
#include "bitmap.h"

#define ENTRY_COUNT 0x90000
#define MEMORMY_MAP 0x90010


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
  

  terminal_initialize();
  pic_remap();
  INITIALIZE_IDT(); 
  write_to_terminal("----------------------------------------------",WHITE);
  write_to_terminal("Displaying Memory Info!: ",WHITE);
  write_to_terminal("----------------------------------------------",WHITE);


  uint8_t count = *(uint8_t*)ENTRY_COUNT;
  MemoryMapEntry* mem = (MemoryMapEntry*)MEMORMY_MAP;
  uint64_t tot_mem =0;

  write_to_terminal("Entry Count is:%i",WHITE,count);
  for(int i=0;i<count;i++)
  {
  
    uint64_t ba = mem[i].baseAddress;
    uint64_t len = mem[i].length;
    uint32_t type = mem[i].type;
    uint32_t acpi = mem[i].acpi;

    if(type==1) tot_mem += len;

    //from the output notice  the large chunnk of memory starting from the 1MB mark :)
    write_to_terminal("Base:%llx, Length:%llu, Type:%u,ACPI:%u",WHITE,ba,len,type,acpi);
  }
  write_to_terminal("----------------------------------------------",WHITE);
  write_to_terminal("TOTAL USABLE MEMORY AVAILABLE IS: %llu MB",WHITE,tot_mem/(1024*1024));

  BITMAP bmp1;
  bitmap_init(&bmp1,800000,133038080);
  uint32_t x;
  if(bitmap_set_range(&bmp1,1,&x))
  {
    write_to_terminal("successfully allocated at address %llu",WHITE,x);
  }
  else
  {
    write_to_terminal("allocation failed!",WHITE);
  }

  while(1)
  {
    
  }
}