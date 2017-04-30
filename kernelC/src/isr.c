/**
 * ISR - Interrupt Service Routine - source file
 */

#include "idt.h"
#include "isr.h"
#include "vga.h"

void isrInstall()
{
  idtSetGate(0, (int64u) isr0, 0x08, 0x8E);
  idtSetGate(1, (int64u) isr1, 0x08, 0x8E);
  idtSetGate(2, (int64u) isr2, 0x08, 0x8E);
  idtSetGate(3, (int64u) isr3, 0x08, 0x8E);
  idtSetGate(4, (int64u) isr4, 0x08, 0x8E);
  idtSetGate(5, (int64u) isr5, 0x08, 0x8E);
  idtSetGate(6, (int64u) isr6, 0x08, 0x8E);
  idtSetGate(7, (int64u) isr7, 0x08, 0x8E);
  idtSetGate(8, (int64u) isr8, 0x08, 0x8E);
  idtSetGate(9, (int64u) isr9, 0x08, 0x8E);
  idtSetGate(10, (int64u) isr10, 0x08, 0x8E);
  idtSetGate(11, (int64u) isr11, 0x08, 0x8E);
  idtSetGate(12, (int64u) isr12, 0x08, 0x8E);
  idtSetGate(13, (int64u) isr13, 0x08, 0x8E);
  idtSetGate(14, (int64u) isr14, 0x08, 0x8E);
  idtSetGate(15, (int64u) isr15, 0x08, 0x8E);
  idtSetGate(16, (int64u) isr16, 0x08, 0x8E);
  idtSetGate(17, (int64u) isr17, 0x08, 0x8E);
  idtSetGate(18, (int64u) isr18, 0x08, 0x8E);
  idtSetGate(19, (int64u) isr19, 0x08, 0x8E);
  idtSetGate(20, (int64u) isr20, 0x08, 0x8E);
  idtSetGate(21, (int64u) isr21, 0x08, 0x8E);
  idtSetGate(22, (int64u) isr22, 0x08, 0x8E);
  idtSetGate(23, (int64u) isr23, 0x08, 0x8E);
  idtSetGate(24, (int64u) isr24, 0x08, 0x8E);
  idtSetGate(25, (int64u) isr25, 0x08, 0x8E);
  idtSetGate(26, (int64u) isr26, 0x08, 0x8E);
  idtSetGate(27, (int64u) isr27, 0x08, 0x8E);
  idtSetGate(28, (int64u) isr28, 0x08, 0x8E);
  idtSetGate(29, (int64u) isr29, 0x08, 0x8E);
  idtSetGate(30, (int64u) isr30, 0x08, 0x8E);
  idtSetGate(31, (int64u) isr31, 0x08, 0x8E);
}

// Error messages
char *exceptionMessages[] =
    {
        "Divide By Zero Exception",
        "Debug Exception",
        "Non Maskable Interrupt Exception",
        "Breakpoint",
        "Overflow",
        "Out of Bounds Exception",
        "Invalid Opcode Exception",
        "Coprocessor Not Available Exception",
        "Double Fault Exception",
        "Coprocessor Segment Overrun Exception",
        "Bad TSS Exception",
        "Segment Not Present Exception",
        "Stack Fault Exception",
        "General Protection Fault",
        "Page Fault Exception",
        "Reserved Exception",
        "Floating Point Exception",
        "Alignment Check Exception",
        "Machine Check Exception",
        "Reserved Exception",
        "Reserved Exception",
        "Reserved Exception",
        "Reserved Exception",
        "Reserved Exception",
        "Reserved Exception",
        "Reserved Exception",
        "Reserved Exception",
        "Reserved Exception",
        "Reserved Exception",
        "Reserved Exception",
        "Reserved Exception",
        "Reserved Exception"
    };

// interrupt handler
void fault_handler(struct regs *r)
{
  if(r->int_no < 32)
  {
    putch('\n');

    setColor(LIGHT_RED, BLACK);

    puts(exceptionMessages[r->int_no]);
    puts(" - exception. System halt!\n");
    for (;;);
  }
}
