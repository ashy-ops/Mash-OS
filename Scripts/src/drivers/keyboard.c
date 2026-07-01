#include "keyboard.h"
#include "shell.h"
#include "display.h"

static int shift_active = 0;
bool SHELL_ACTIVE = false;

char keyboard_buffer[2000] = {0};
uint16_t buffer_len = 0;
uint16_t buffer_pos = 0;

//Scancode set 1
static const char scancode_to_ascii_lowercase[] = {
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
  '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
    0,  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',   0,
   '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/',   0, '*',   0, ' '
};

static const char scancode_to_ascii_uppercase[] = {
    0,  27, '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', '\b',
  '\t', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\n',
    0,  'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '"', '~',   0,
    '|', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '?',   0, '*',   0, ' '
};



void initialize_keyboard()
{
    isr_register_handler(KEYBOARD_INTERRUPT, &keyboard_handler);
}

void keyboard_handler(registers_t* regs __attribute__((unused)))
{
    uint8_t scancode = inb(PS2_DATA);

    //break codes(key releases) checks if 7th bit active
    if (scancode & 0x80) {
        //bits 6-0 are the key identifiers, hence clearing the 8th bit to 0
        uint8_t make_code = scancode & 0x7F;
        if (make_code == 0x2A || make_code == 0x36) shift_active = 0;
        return;
    }

    //make codes(key presses) if its not a break code its def a make code hence not checking!
    //dealing with shift press
    if (scancode == 0x2A || scancode == 0x36) {
        shift_active = 1;
        return; //not to print something for shift key itself
    }

    //Check for ESC key to initialize shell
    if (scancode == 1) {
        if (!SHELL_ACTIVE) {
            initialize_shell();
        }
        return;
    }

    //Only process keyboard input when shell is active
    if (!SHELL_ACTIVE) {
        return;
    }

    //dealing with enter
    if(scancode == 0x1C)
    {
        new_line();
        parse_command();
        buffer_len = 0;
        buffer_pos = 0;
        return;
    }
    
    // if(scancode == 0x4B)
    // {
    //     if(buffer_pos>0)
    //     {
    //         buffer_pos--;
    //         move_cursor_left();
    //     }
    //     return;
    // }

    // if(scancode == 0x4D)
    // {
    //     if(buffer_pos<buffer_len)
    //     {
    //         buffer_pos++;
    //         move_cursor_right();
    //     }
    //     return;
    // }
    //dealing with backspace!
    if(scancode == 0x0E)
    {
        if(buffer_len>0)
        {
            buffer_len--;
            buffer_pos--;
            terminal_buffer[buffer_pos] = vga_entry(' ',vga_entry_color(terminal_color,terminal_color));
            cur_column--;
            if(cur_column<0)
            {
                cur_column=0;
                cur_row--;
            }
        }
        return;
    }

    //else print ascii and buffer
    if (scancode < sizeof(scancode_to_ascii_lowercase))
    {
        char ascii_char = 0;//its the value 0 not the character 0(ascii=48)

        if (shift_active) ascii_char = scancode_to_ascii_uppercase[scancode];
        else ascii_char = scancode_to_ascii_lowercase[scancode];

        //27 is for escape key



        if (ascii_char != 0 && ascii_char != 27)
        {
            char prev = keyboard_buffer[buffer_pos];
            for(int i=buffer_pos+1; i<=buffer_len;i++)
            {
                char temp = keyboard_buffer[i];
                keyboard_buffer[i] = prev;
                prev = temp;
            }
            //have to update the visual text!
            
            write_to_terminal("%c", WHITE, ascii_char); //putc automatically moves the cursor!
            if(buffer_len<2000) keyboard_buffer[buffer_pos] = ascii_char;
            buffer_len++;
            buffer_pos++;
        }

    }
}