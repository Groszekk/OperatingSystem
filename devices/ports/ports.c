#include "ports.h"

void outb(unsigned short port, unsigned char data)
{
    __asm__ __volatile__("out %%al, %%dx" : : "a" (data), "d" (port));
}

unsigned char inb(unsigned short port)
{
    unsigned char result;

    __asm__("in %%dx, %%al" : "=a" (result) : "d" (port));
    return result;
}

void wordout(unsigned short port, unsigned short data)
{
    __asm__ __volatile__("out %%ax, %%dx" : : "a" (data), "d" (port));
}

unsigned short wordin(unsigned short port)
{
    unsigned short result;
    __asm__("in %%dx, %%ax" : "=a" (result) : "d" (port));
    return result;
}

void outl(unsigned int port, unsigned int data)
{
	   __asm__ __volatile__("outl %%eax, %%dx" : : "d" (port), "a" (data));
}