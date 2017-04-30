###
CC = gcc
CC_FLAGS =


###
default: os

###
createimg: createimg.c
	@$(CC) $(CC_FLAGS) -o createimg createimg.c
	@echo createimg DONE.

###
write2disk: write2disk.c
	@$(CC) $(CC_FLAGS) -o write2disk write2disk.c
	@echo write2disk DONE.

###
os:
ifeq ("$(wildcard ../bootloader/bootloader.bin)","")
	@echo No bootloader binary found in ../bootloader/bootloader.bin, trying to make one now...
	@cd ../bootloader && make
endif

ifeq ("$(wildcard ../kernelC/kernel.bin)","")
	@echo No kernel binary found in ../kernelC/kernel.bin, trying to make one now...
	@cd ../kernelC && make
endif

ifeq ("$(wildcard createimg)","")
	@echo "createimg" tool is missing, making one now...
	@make createimg
endif

	@./createimg os.img ../bootloader/bootloader.bin ../kernelC/kernel.bin
	@echo OS making is done.
	@echo If you want to write it to binary image with offset [Useful if you are testing on virtual machine] you can execute command: write2disk os.img [DESTINATION] [OFFSET-IN-HEX].
	@echo If you do not have it, you can make it with \"make write2disk\".
	@echo Usage example for VirtualBox would be: write2disk os.img drive.vdi 200000

###
clean:
	@$(RM) createimg write2disk os.img *~

clean-all:
	@$(RM) createimg write2disk os.img *~
	@cd ../bootloader && make clean
	@cd ../kernelC && make clean
