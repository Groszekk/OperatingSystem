#include "handler.h"
#include "../../devices/screen/screen.h"
#include "../ISR/isr.h"

idt_entry idt[256];
idtr idtp;

void clear_idt(idt_entry** _idt)
{
    for(int i = 0; i <= (int)sizeof(idt); i++)
    {
        _idt[i]->base_l = 0;
        _idt[i]->base_h = 0;
        _idt[i]->seg_selector = 0;
        _idt[i]->zero = 0;
        _idt[i]->flags = 0;
    }
}

void idt_set_gate(unsigned char num, unsigned long base)
{
    idt[num].base_l = (base & 0xffff);
    idt[num].base_h = ((base >> 16) & 0xffff);
    idt[num].seg_selector = 0x08;
    idt[num].zero = 0;
    idt[num].flags = 0x8E;

}

void idt_install(void)
{
    isr_install();
    idtp.limit = (sizeof(idt_entry) * 256) - 1;
    idtp.base = (unsigned int)&idt;
    clear_idt(idt);

    __asm__ __volatile__("lidtl (%0)" : : "r" (&idtp));
}