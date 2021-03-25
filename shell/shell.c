#include "shell.h"
#include "../devices/screen/screen.h"
#include "../libc/string.h"
#include "../libc/malloc/malloc.h"

// <ugly>

void init_shell(void)
{
    kprint(">>> ");
}

void print_heap_var(int* addr)
{
    char str[1];
    int_to_ascii((int)*addr, str);
    kprint(str);
    kprint(" ");
    char str_addr[8];
    hex_to_ascii(addr, str_addr);
    kprint(str_addr);
    kprint("\n");
}

int malloc_test(char* cmd) 
{
    int len = strlen(cmd);
    char full_word[len];
    int cmd_c = 0;
    int _cmd_c = 0;
    int arg = 0;
    for(int i = 0; i < len; i++)
    {
        if(cmd[i] == ' ')
        {
            cmd_c = i;
            _cmd_c = i;
            cmd_c++;
            while(cmd_c != len)
            {
                arg++;
                cmd_c++;
            }
            break;
        }else
        {
            full_word[i] = cmd[i];
        }
    }

    char _cmd[_cmd_c];
    for(int i = 0; i <= strlen(_cmd); i++)
    {
        _cmd[i] = full_word[i];
    }
    
    _cmd_c += 1;

    if(strcmp(_cmd, "MALLOC") == 0)
    {
        char s_arg[arg];
        for(int i = 0; i <= arg; i++)
        {
            s_arg[i] = cmd[_cmd_c++];
        }

        int* var = kmalloc(sizeof(int));
        *var = atoi(s_arg);
        if(*var == 1901129 || *var <= 0)
        {
            kprint("invalid argument\n");
            return 2;
        }
        print_heap_var(var);
        return 2;
    }
    return 0;
}

void input(char* cmd)
{
    
    if(strcmp(cmd, "STOP") == 0)
    {
        __asm__ __volatile__("hlt");
    }else if(malloc_test(cmd) == 2)
    {
        init_shell();
        return;
    }else
    {
        kprint("command ");
        kprint(cmd);
        kprint(" not found\n");
    }
    
    init_shell();
}

// </ugly>