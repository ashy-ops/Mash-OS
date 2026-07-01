#pragma once
#include "isr.h"
#include "io.h"
#include <stdint.h>
#include "display.h"


#define KEYBOARD_INTERRUPT 33
#define PS2_DATA    0x60 // Read or Write
#define PS2_STATUS  0x64 // Read
#define PS2_WRITE   0x64 // Write



extern char keyboard_buffer[2000];
extern uint16_t buffer_len;
extern uint16_t buffer_pos; //declared here and initialized in keyboard.c!
void initialize_keyboard();
void keyboard_handler(registers_t* regs);
