# todo: do clean makefile structure

OBJECTS = screen.o interrupt_handler.o isr.o aisr.o

all:
	nasm -f elf32 boot.asm -o boot.o
	gcc -fno-pie -m32 kernel.c boot.o -o kernel.bin -nostdlib -ffreestanding -std=c99 -mno-red-zone -fno-exceptions -nostdlib -Wall -Wextra -T link.ld

run:
	nasm -f elf32 boot/boot.asm -o boot.o
	gcc -fno-pie -m32 devices/screen/screen.c -c -o screen.o -nostdlib -ffreestanding -std=c99 -mno-red-zone -fno-exceptions -nostdlib -Wall -Wextra
	gcc -fno-pie -m32 kernel/IDT/handler.c -c -o interrupt_handler.o -nostdlib -ffreestanding -std=c99 -mno-red-zone -fno-exceptions -nostdlib -Wall -Wextra

	gcc -fno-pie -m32 kernel/ISR/isr.c -c -o isr.o -nostdlib -ffreestanding -std=c99 -mno-red-zone -fno-exceptions -nostdlib -Wall -Wextra

	nasm -f elf32 kernel/ISR/isr.asm -o aisr.o

	gcc -fno-pie -m32 kernel/kernel.c boot.o ${OBJECTS} -o kernel.bin -nostdlib -ffreestanding -std=c99 -mno-red-zone -fno-exceptions -nostdlib -Wall -Wextra -T link.ld
	qemu-system-i386 -fda kernel.bin