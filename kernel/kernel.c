#include "../devices/screen/screen.h"
#include "IDT/handler.h"
#include "ISR/isr.h"
#include "IRQ/irq.h"

void kmain(void)
{
    idt_install();
    irq_install();
    kprint("Hello World");
}