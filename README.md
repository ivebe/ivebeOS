# ivebeOS
Amateur operating system created a couple of years ago. It has bootloader in ASM, and kernel in C (smaller portion is also ASM).

Attached are also helper programs in `tools` directory, with VirtualBox virtual disk that has OS already set on it. There is also a binary image, if you don't want to compile.

For those who want to compile the OS, you have makefiles set in bootloader, kernelC, and also in tools directory. Simple procedure for compiling would look like this:

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
