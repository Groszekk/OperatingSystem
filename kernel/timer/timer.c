#include "timer.h"
#include "../../devices/screen/screen.h"
#include "../../libc/string.h"
#include "../ISR/isr.h"
#include "../../devices/ports/ports.h"

unsigned int tick = 0;

void timer_callback(void)
{
    tick++;
}

void send_cmd(unsigned char low, unsigned char high)
{
    outb(0x43, 0x36);
    outb(0x40, low);
    outb(0x40, high);
}

void init_timer(unsigned int freq)
{
    register_interrupt_handler(IRQ0, timer_callback);

    unsigned int divisor = 1193182  / freq; // 1193182  Hz
    unsigned char low  = (unsigned char)(divisor & 0xFF);
    unsigned char high = (unsigned char)((divisor >> 8) & 0xFF);
    send_cmd(low, high);
}

