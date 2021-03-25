# todo: do clean makefile structure

OBJECTS = screen.o interrupt_handler.o isr.o aisr.o ports.o mem.o string.o timer.o keyboard.o irq.o aisq.o shell.o malloc.o

all:
	nasm -f elf32 boot.asm -o boot.o
	gcc -fno-pie -m32 kernel.c boot.o -o kernel.bin -nostdlib -ffreestanding -std=c99 -mno-red-zone -fno-exceptions -nostdlib -Wall -Wextra -T link.ld

run:
	nasm -f elf32 boot/boot.asm -o boot.o
	gcc -fno-pie -m32 devices/screen/screen.c -c -o screen.o -nostdlib -ffreestanding -std=c99 -mno-red-zone -fno-exceptions -nostdlib -Wall -Wextra
	gcc -fno-pie -m32 devices/ports/ports.c -c -o ports.o -nostdlib -ffreestanding -std=c99 -mno-red-zone -fno-exceptions -nostdlib -Wall -Wextra

	gcc -fno-pie -m32 kernel/IDT/handler.c -c -o interrupt_handler.o -nostdlib -ffreestanding -std=c99 -mno-red-zone -fno-exceptions -nostdlib -Wall -Wextra

	gcc -fno-pie -m32 kernel/ISR/isr.c -c -o isr.o -nostdlib -ffreestanding -std=c99 -mno-red-zone -fno-exceptions -nostdlib -Wall -Wextra

	gcc -fno-pie -m32 kernel/IRQ/irq.c -c -o irq.o -nostdlib -ffreestanding -std=c99 -mno-red-zone -fno-exceptions -nostdlib -Wall -Wextra

	gcc -fno-pie -m32 libc/mem.c -c -o mem.o -nostdlib -ffreestanding -std=c99 -mno-red-zone -fno-exceptions -nostdlib -Wall -Wextra
	gcc -fno-pie -m32 libc/string.c -c -o string.o -nostdlib -ffreestanding -std=c99 -mno-red-zone -fno-exceptions -nostdlib -Wall -Wextra
	gcc -fno-pie -m32 kernel/timer/timer.c -c -o timer.o -nostdlib -ffreestanding -std=c99 -mno-red-zone -fno-exceptions -nostdlib -Wall -Wextra
	gcc -fno-pie -m32 devices/keyboard/keyboard.c -c -o keyboard.o -nostdlib -ffreestanding -std=c99 -mno-red-zone -fno-exceptions -nostdlib -Wall -Wextra

	gcc -fno-pie -m32 shell/shell.c -c -o shell.o -nostdlib -ffreestanding -std=c99 -mno-red-zone -fno-exceptions -nostdlib -Wall -Wextra

	gcc -fno-pie -m32 libc/malloc/malloc.c -c -o malloc.o -nostdlib -ffreestanding -std=c99 -mno-red-zone -fno-exceptions -nostdlib -Wall -Wextra

	nasm -f elf32 kernel/ISR/isr.asm -o aisr.o
	nasm -f elf32 kernel/IRQ/irq.asm -o aisq.o

	gcc -fno-pie -m32 kernel/kernel.c boot.o ${OBJECTS} -o kernel.bin -nostdlib -ffreestanding -std=c99 -mno-red-zone -fno-exceptions -nostdlib -Wall -Wextra -T link.ld
	qemu-system-i386 -fda kernel.bin