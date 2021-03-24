#include "../devices/screen/screen.h"
#include "IDT/handler.h"
#include "ISR/isr.h"
#include "IRQ/irq.h"
#include "../shell/shell.h"

void kmain(void)
{
    idt_install();
    irq_install();
    init_shell();
}