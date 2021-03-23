#include "../ISR/isr.h"
#include "../../devices/ports/ports.h"
#include "../../devices/keyboard/keyboard.h"
#include "../timer/timer.h"

void irq_handler(registers r)
{
    // after every interrupt, need to send EOI

    // input ISR register value to PIC master/slave circuit
    if(r.int_no >= 40) outb(0xA0, 0x20); // slave
    outb(0x20, 0x20); // master

    if(interrupt_handlers[r.int_no] != 0)
    {
        isr_t handler = interrupt_handlers[r.int_no];
        handler(r);
    }
}

void irq_install(void)
{
    __asm__ __volatile__("sti");
    init_timer(50);
    init_keyboard();
}