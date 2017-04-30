#
# Creates x86 binary on x64 system. If you run on different system
# you may have to modify Makefile
#
CC = gcc
LD = gcc
NASM = nasm

CC_FLAGS   = -m32 -Wall -O0 -fno-asynchronous-unwind-tables -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin
LD_FLAGS   = -m32 -O0 -nostdlib -T link.ld
NASM_FLAGS = -f aout
INCLUDES   = -isystem ./src/inc

###
default: objs

###
objs: obj/start.o obj/kernel.o obj/system.o obj/vga.o obj/idt.o obj/isr.o obj/io.o obj/irq.o obj/timer.o obj/kb.o obj/gdt.o obj/bin.o
	@$(LD) $(LD_FLAGS) -o kernel.bin obj/start.o obj/kernel.o obj/system.o obj/vga.o obj/idt.o obj/isr.o obj/io.o obj/irq.o obj/timer.o obj/kb.o obj/gdt.o obj/bin.o
	@echo Done.

###
obj/start.o:  src/start.asm
	@$(NASM) $(NASM_FLAGS) -o obj/start.o src/start.asm

###
obj/%.o: src/%.c
	@$(CC) $(CC_FLAGS) $(INCLUDES) -c -o $@ $<

###
clean:
	@$(RM) kernel.bin obj/*.o *~
