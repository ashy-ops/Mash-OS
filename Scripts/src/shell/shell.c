#include "shell.h"


static const char* programs[] = {
    "program0",
    "program1"
};

void initialize_shell()
{
    SHELL_ACTIVE = true;
    clear_screen();
    write_to_terminal("nebulaOS$: ",WHITE);

    //clear keyboard buffer
    for(int i = 0; i < 2000; i++) {
        keyboard_buffer[i] = 0;
    }
    buffer_len = 0;
    buffer_pos = 0;
}


void delete_char()
{

}

void parse_command()
{
    int state = STATE_READ_COMMAND; // 0: reading command, 1: reading args
    char command[32] = {0};
    char args[100] = {0};
    int cmd_idx = 0;
    int arg_idx = 0;
    
    for(int i = 0; i<buffer_len; i++) {
        char c = keyboard_buffer[i];
        

        if(state == STATE_READ_COMMAND)
        {
            //as command is written before any space!
            if(c == ' ')state = 1;
            else if(cmd_idx < 31) command[cmd_idx++] = c;
        }
        else //for argument buffer 
        {
            if(arg_idx < 99) args[arg_idx++] = c;
            
        }
    }
    
    command[cmd_idx] = 0;
    args[arg_idx] = 0;
    
    //clear keyboard buffer after parsing
    for(int i = 0; i < 2000; i++) {
        keyboard_buffer[i] = 0;
    }
    

    if(command[0] == 0)
    {
        //empty command
        write_to_terminal("nebulaOS:$ ", WHITE);
        return;
    }
    
    //echo command
    if(command[0] == 'e' && command[1] == 'c' && command[2] == 'h' && command[3] == 'o' && command[4] == 0)
    {
        if(args[0] != 0) write_to_terminal("%s\n", WHITE, args);
        else write_to_terminal("\n", WHITE);
        
        write_to_terminal("nebulaOS:$ ", WHITE);
        return;
    }
    
    //lp command
    if(command[0] == 'l' && command[1] == 'p' && command[2] == 0) 
    {
        write_to_terminal("Available programs:\n", WHITE);
        for(int i = 0; i < 10; i++) write_to_terminal("  %d: %s\n", WHITE, i, programs[i]);
        write_to_terminal("nebulaOS:$ ", WHITE);
        return;
    }
    
    //run command
    if(command[0] == 'r' && command[1] == 'u' && command[2] == 'n' && command[3] == ' ')
    {
        int program_num = 0;
        // Parse the number after "run "
        for(int i = 4; args[i-4] != 0; i++)
        {
            char c = args[i-4];
            
            if(c >= '0' && c <= '9') program_num = program_num * 10 + (c - '0');
            else
            {
                program_num = -1; // Invalid
                break;
            }
        }
        
        if(program_num >= 0 && program_num <= 9) 
        {
            write_to_terminal("Running program %d: %s\n", WHITE, program_num, programs[program_num]);
            SHELL_ACTIVE = false;
            return;
        } else {
            write_to_terminal("Invalid program number. Use 0-9.\n", WHITE);
            write_to_terminal("nebulaOS:$ ", WHITE);
            return;
        }
    }
    
    // Invalid command
    write_to_terminal("Invalid command\n", WHITE);

    write_to_terminal("nebulaOS:$ ", WHITE);
}