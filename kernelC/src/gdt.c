/**
 * GDT - Global Descriptor Table - source file
 */

#include "gdt.h"

// GDT have 3 segments, first is mandatory null segment, code segment, and data segment
struct gdtEntry gdt[3];
struct gdtPointer gdt_p;

void gdtSetDescriptor(int32 num, int64u base, int64u limit, int8u access, int8u gran)
{
  gdt[num].base_low = (base & 0xFFFF);
  gdt[num].base_middle = (base >> 16) & 0xFF;
  gdt[num].base_high = (base >> 24) & 0xFF;

  gdt[num].limit_low = (limit & 0xFFFF);
  gdt[num].granularity = ((limit >> 16) & 0x0F);

  gdt[num].granularity |= (gran & 0xF0);
  gdt[num].access = access;
}

// creating of GDT table, and calling ASM function which will tell CPU where is GDT
void gdtInstall()
{
  gdt_p.limit = (sizeof(struct gdtEntry) * 3) - 1;
  gdt_p.base = (int32u) & gdt;

  //mandatory null deskriptor
  gdtSetDescriptor(0, 0, 0, 0, 0);

  // Code segment. Base address = 0, Limit 4GB, Granularity set in KB, 32-bit opcode
  gdtSetDescriptor(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);

  // Data segment, only difference is in one flag
  gdtSetDescriptor(2, 0, 0xFFFFFFFF, 0x92, 0xCF);

  //call ASM function
  gdtFlush();
}
