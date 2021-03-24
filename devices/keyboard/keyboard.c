#include "keyboard.h"
#include "consts.h"
#include "../ports/ports.h"
#include "../../kernel/ISR/isr.h"
#include "../screen/screen.h"
#include "../../libc/string.h"
#include "../../libc/bool.h"
#include "../../shell/shell.h"

typedef unsigned char bool;

static bool caps;
static char key_buff[0x100];
static void keys_controller(unsigned char scancode);

static void keyboard_callback(void)
{
    unsigned char scancode = inb(0x60); // get scan code from 0x60 port
    keys_controller(scancode);
}

void init_keyboard()
{
   register_interrupt_handler(IRQ1, keyboard_callback); 
}

void keys_controller(unsigned char scancode)
{
    switch(scancode)
    {
        case 0x0E:
        {
            if(key_buff[0])
            {
                backspace(key_buff);
                kprint_backspace();
            }
            break;
        }

        case 0x1C:
        {
            kprint("\n");
            input(key_buff);
            key_buff[0] = '\0';
            break;
        }
        
        case 0x3A: caps = !caps;
            break;

        case 0x2A: caps = true;
        break;

        default:
        {
            if(scancode >> 7 == 0/*pressed*/)
            {
                char letter = scan_a[(int)scancode];
                char string[2] = {letter, '\0'};
                append(key_buff, letter);
                if(!caps) // temporary solution
                    kprint(to_lower(string));
                else kprint(string);
            }
            if(scancode == 0xAA && scancode >> 7 == 1)
            {
                caps = false;
            }
            break;
        }
    }
}