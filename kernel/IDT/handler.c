#include "handler.h"
#include "../../devices/screen/screen.h"

struct idt_entry idt[256];
struct idtr idtp;

extern void idt_load();

void clear_idt(struct idt_entry** _idt)
{
    for(int i = 0; i <= sizeof(idt); i++)
    {
        _idt[i]->base_l = 0;
        _idt[i]->base_h = 0;
        _idt[i]->seg_selector = 0;
        _idt[i]->zero = 0;
        _idt[i]->flags = 0;
    }
}

void idt_set_gate(unsigned char num, unsigned long base/*, unsigned short sel, unsigned char flags*/)
{
    idt[num].base_l = (base & 0xffff);
    idt[num].base_h = (base >> 16 & 0xffff);
    idt[num].seg_selector = 0x8;
    idt[num].zero = 0;
    idt[num].flags = 0x8E;

}

void idt_install(void)
{
    isr_install();
    idtp.limit = (sizeof(struct idt_entry) * 256) - 1;
    idtp.base = &idt;
    clear_idt(&idt);

    idt_load();
}