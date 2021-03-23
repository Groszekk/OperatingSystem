#ifndef PORTS_H
#define PORTS_H

void outb(unsigned short port, unsigned char data);
unsigned char inb(unsigned short port);
void wordout(unsigned short port, unsigned short data);
unsigned short wordin(unsigned short port);
void outl(unsigned int port, unsigned int data);

unsigned short inw(unsigned short int port);

#endif