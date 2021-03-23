#include "isr.h"
#include "consts.h"
#include "../IDT/handler.h"
#include "../../devices/screen/screen.h"
#include "../../devices/ports/ports.h"
#include "../timer/timer.h"
#include "../../devices/keyboard/keyboard.h"

isr_t interrupt_handlers[0x100];

void isr_install(void)
{
    // ISRs
    idt_set_gate(0, (unsigned int)isr0);
    idt_set_gate(1, (unsigned int)isr1);
    idt_set_gate(2, (unsigned int)isr2);
    idt_set_gate(3, (unsigned int)isr3);
    idt_set_gate(4, (unsigned int)isr4);
    idt_set_gate(5, (unsigned int)isr5);
    idt_set_gate(6, (unsigned int)isr6);
    idt_set_gate(7, (unsigned int)isr7);
    idt_set_gate(8, (unsigned int)isr8);
    idt_set_gate(9, (unsigned int)isr9);
    idt_set_gate(10, (unsigned int)isr10);
    idt_set_gate(11, (unsigned int)isr11);
    idt_set_gate(12, (unsigned int)isr12);
    idt_set_gate(13, (unsigned int)isr13);
    idt_set_gate(14, (unsigned int)isr14);
    idt_set_gate(15, (unsigned int)isr15);
    idt_set_gate(16, (unsigned int)isr16);
    idt_set_gate(17, (unsigned int)isr17);
    idt_set_gate(18, (unsigned int)isr18);
    idt_set_gate(19, (unsigned int)isr19);
    idt_set_gate(20, (unsigned int)isr20);
    idt_set_gate(21, (unsigned int)isr21);
    idt_set_gate(22, (unsigned int)isr22);
    idt_set_gate(23, (unsigned int)isr23);
    idt_set_gate(24, (unsigned int)isr24);
    idt_set_gate(25, (unsigned int)isr25);
    idt_set_gate(26, (unsigned int)isr26);
    idt_set_gate(27, (unsigned int)isr27);
    idt_set_gate(28, (unsigned int)isr28);
    idt_set_gate(29, (unsigned int)isr29);
    idt_set_gate(30, (unsigned int)isr30);
    idt_set_gate(31, (unsigned int)isr31);

    // PIC
    outb(0x20, 0x11);
    outb(0xA0, 0x11);
    outb(0x21, 0x20);
    outb(0xA1, 0x28);
    outb(0x21, 0x04);
    outb(0xA1, 0x02);
    outb(0x21, 0x01);
    outb(0xA1, 0x01);
    outb(0x21, 0x0);
    outb(0xA1, 0x0);

    // IRQs
    idt_set_gate(32, (unsigned int)irq0);
    idt_set_gate(33, (unsigned int)irq1);
    idt_set_gate(34, (unsigned int)irq2);
    idt_set_gate(35, (unsigned int)irq3);
    idt_set_gate(36, (unsigned int)irq4);
    idt_set_gate(37, (unsigned int)irq5);
    idt_set_gate(38, (unsigned int)irq6);
    idt_set_gate(39, (unsigned int)irq7);
    idt_set_gate(40, (unsigned int)irq8);
    idt_set_gate(41, (unsigned int)irq9);
    idt_set_gate(42, (unsigned int)irq10);
    idt_set_gate(43, (unsigned int)irq11);
    idt_set_gate(44, (unsigned int)irq12);
    idt_set_gate(45, (unsigned int)irq13);
    idt_set_gate(46, (unsigned int)irq14);
    idt_set_gate(47, (unsigned int)irq15);
}

void isr_handler(registers r)
{
    if(r.int_no >= 19)
    {
        kprint("Reserved");
    }else if(r.int_no < 19)
    {
        kprint(exception[r.int_no]);
    }

    kprint("\n");
}

void register_interrupt_handler(unsigned char n, isr_t handler)
{
    interrupt_handlers[n] = handler;
}