#ifndef ISR_H
#define ISR_H

extern void isr0();
extern void isr2();

typedef struct
{
   unsigned int ds;
   unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;
   unsigned int int2, int_no, err_code;
   unsigned int eip, cs, eflags, useresp, ss;
}registers_t;

void isr_install(void);

void isr_handler(registers_t r);

#endif