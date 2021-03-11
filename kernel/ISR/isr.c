#include "isr.h"
#include "../IDT/handler.h"
#include "../../devices/screen/screen.h"

void isr_install(void)
{
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
}

void int_to_ascii(int n, char str[])
{
    int i, sign;
    if ((sign = n) < 0) n = -n;
    i = 0;
    do {
        str[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);

    if (sign < 0) str[i++] = '-';
    str[i] = '\0';
}

char *exception[] = {
    "Division By Zero",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Into Detected Overflow",
    "Out of Bounds",
    "Invalid Opcode",
    "No Coprocessor",
    "Double Fault",
    "Coprocessor Segment Overrun",
    "Bad TSS",
    "Segment Not Present",
    "Stack Fault",
    "General Protection Fault",
    "Page Fault",
    "Unknown Interrupt",
    "Coprocessor Fault",
    "Alignment Check",
    "Machine Check"
};

void isr_handler(registers r)
{
    if(r.int_no >= 19)
    {
        print("Reserved");
    }else if(r.int_no < 19)
    {
        print(exception[r.int_no]);
    }

    print("\n");
}