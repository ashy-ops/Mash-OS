#include <stdint.h>
#include "display.h"
#include "keyboard.h"
#include <stdbool.h>

#define STATE_READ_COMMAND 0
#define STATE_READ_ARGS 1

extern bool SHELL_ACTIVE;


void initialize_shell();
void delete_char();
void parse_command();

//buffer len
//