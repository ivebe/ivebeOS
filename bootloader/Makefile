###
NASM = nasm
NASM_FLAGS = -f bin

###
default: boot

###
boot:  bootloader.asm
	@$(NASM) $(NASM_FLAGS) -o bootloader.bin bootloader.asm
	@echo Done.

###
clean:
	@$(RM) bootloader.bin *~
