#ifndef HANDLER_H
#define HANDLER_H

typedef struct
{
    unsigned short limit;
    unsigned int base;
}__attribute__((packed)) idtr;

typedef struct
{
    unsigned short base_l;
    unsigned short seg_selector;
    unsigned char zero;
    unsigned char flags;
    unsigned short base_h;
}__attribute__((packed)) idt_entry;

void idt_install(void);
void idt_set_gate(unsigned char num, unsigned long base);

#endif