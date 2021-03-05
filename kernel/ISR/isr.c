#include "isr.h"
#include "../IDT/handler.h"
#include "../../devices/screen/screen.h"

void isr_install(void)
{
    idt_set_gate(0, (unsigned int)isr0);
    idt_set_gate(2, (unsigned int)isr2);
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

void isr_handler(registers_t r)
{
    print("reviced interrupt: ");
    char s[3];
    int_to_ascii(r.err_code, s);
    print(s);
}