#include <stdint.h>
#include "display.h"
#include "isr.h"
#include "debug.h"

uint8_t debug_list[] = {0,1,2,3,4,5,6,7,8,9,10};
void debug_interrupts()
{
    for(int i=0;i<sizeof(debug_list)/sizeof(debug_list[0]); i++)
    {
        registers_t fake_regs = {0};
        fake_regs.interrupt = i;
        isr_handler(&fake_regs);
    }
}
