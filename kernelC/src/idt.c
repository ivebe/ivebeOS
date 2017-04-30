/**
 * IDT - Interrupt Descriptor Table - source file
 */

#include "system.h"
#include "idt.h"

// define IDT with 256 entries
struct idtEntry idt[256];
struct idtPointer idt_p;

//add to IDT
void idtSetGate(int8u num, int64u base, int16u sel, int8u flags)
{
  idt[num].base_lo = (base & 0xFFFF);
  idt[num].base_hi = (base >> 16) & 0xFFFF;

  idt[num].sel = sel;
  idt[num].always0 = 0;
  idt[num].flags = flags;
}

// setup IDT table and call ASM function
void idtInstall()
{
  idt_p.limit = (sizeof(struct idtEntry) * 256) - 1;
  idt_p.base = (int32u) & idt;

  //set IDT to 0 for all 256 entries
  memset(&idt, 0, sizeof(struct idtEntry) * 256);

  //ASM function
  idtLoad();
}
