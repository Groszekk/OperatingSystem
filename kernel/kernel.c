#include "../devices/screen/screen.h"
#include "IDT/handler.h"
#include "ISR/isr.h"

void kmain(void)
{
    idt_install();
    int a = 3 / 0; // test ISR - division by zero
    print("Hello World\n");
}