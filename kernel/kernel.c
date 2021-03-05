#include "../devices/screen/screen.h"
#include "IDT/handler.h"
#include "ISR/isr.h"

void kmain(void)
{
    idt_install();
    print("Hello World");
}