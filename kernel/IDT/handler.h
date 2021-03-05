#ifndef HANDLER_H
#define HANDLER_H

struct idtr
{
    unsigned short limit;
    unsigned int base;
}__attribute__((packed));

struct idt_entry
{
    unsigned short base_l;
    unsigned short seg_selector;
    unsigned char zero;
    unsigned char flags;
    unsigned short base_h;
}__attribute__((packed));

void idt_install(void);
void idt_set_gate(unsigned char num, unsigned long base);

#endif