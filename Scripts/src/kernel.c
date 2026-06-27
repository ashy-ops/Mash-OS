#include <stdint.h>
#include "pic.h"
#include "idt.h"
#include "display.h"
#include "bitmap.h"

#define ENTRY_COUNT 0x90000
#define MEMORMY_MAP 0x90010


volatile char* VGA_BUFFER = (volatile char*)0xB8000;

typedef struct 
{
  uint64_t max_free_memory;
  uint64_t max_base_addrs;
} bitmap_data;

typedef struct __attribute__((packed)) {
    uint64_t baseAddress;
    uint64_t length;
    uint32_t type;
    uint32_t acpi; // ACPI 3.0 extended attributes
} MemoryMapEntry;
//uint8_t count = *(uint8_t*)ENTRY_COUNT; Throws error

typedef struct
{
  uint32_t strt_page;
  uint32_t pages_allocated;
} var;

void kernel_main()
{
  

  terminal_initialize();
  pic_remap();
  INITIALIZE_IDT(); 
  write_to_terminal("----------------------------------------------",WHITE);
  write_to_terminal("Displaying Memory Info!: ",WHITE);
  write_to_terminal("----------------------------------------------",WHITE);

  bitmap_data b = {0,0};

  uint8_t count = *(uint8_t*)ENTRY_COUNT;
  MemoryMapEntry* mem = (MemoryMapEntry*)MEMORMY_MAP;
  
  write_to_terminal("Entry Count is:%i",WHITE,count);
  for(int i=0;i<count;i++)
  {
  
    uint64_t ba = mem[i].baseAddress;
    uint64_t len = mem[i].length;
    uint32_t type = mem[i].type;
    uint32_t acpi = mem[i].acpi;

    if(type==1 && b.max_free_memory<len)
    {
      b.max_free_memory = len;
      b.max_base_addrs = ba;
    }

    //from the output notice  the large chunnk of memory starting from the 1MB mark :)
    write_to_terminal("Base:%llx, Length:%llu, Type:%u,ACPI:%u",WHITE,ba,len,type,acpi);
  }

  BITMAP bmp;
  bitmap_init(&bmp,b.max_base_addrs,b.max_free_memory);
  var x;
  
  if(bitmap_set_range(&bmp,20,&x.strt_page))
  {
    x.pages_allocated = 20;
    write_to_terminal("Allocated at:%u and len:%u",WHITE,x.strt_page,x.pages_allocated);
  }
  else write_to_terminal("Allocation Failed!",WHITE);

  bitmap_unset_range(&bmp,x.strt_page,x.pages_allocated);

  var y;
  if(bitmap_set_range(&bmp,20,&y.strt_page))
  {
    y.pages_allocated = 20;
    write_to_terminal("Allocated at:%u and len:%u",WHITE,y.strt_page,y.pages_allocated);
  }
  else write_to_terminal("Allocation Failed!",WHITE);

  while(1)
  {
    
  }
}