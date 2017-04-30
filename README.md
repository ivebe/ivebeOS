# ivebeOS
Amateur operating system created couple of years ago. Have bootloader in ASM, and kernel in C (smaller portion is also ASM).

Attached are also helper programs in `tools` directory, with VirtualBox virtual disk with OS already set on it. There is also binary image if you do not wan't to compile.

For those who want to compile the OS, you have makefiles set in bootloader, kernelC, and also in tools directory. Simple procedute for compiling would look like

```C
cd tools
```

```C
make clean-all
```


```C
make
```


```C
make write2disk
```

```C
./write2disk os.img 4mb_disk.vdi 200000
```

Binary image should go to the first sector of disk, in VirtualBox harddisk starts from ofset 0x200000, that's the 3rd parameter in `write2disk`.
