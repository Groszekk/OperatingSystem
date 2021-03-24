#include "shell.h"
#include "../devices/screen/screen.h"
#include "../libc/string.h"

void init_shell(void)
{
    kprint(">>> ");
}

void input(char* cmd)
{
    if(strcmp(cmd, "STOP") == 0)
    {
       __asm__ __volatile__("hlt");
    }else
    {
        kprint("command ");
        kprint(cmd);
        kprint(" not found\n");
    }
    init_shell();
}