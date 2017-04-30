/**
 * IRQ - Interrupt Requests - source file
 *
 */

#include "irq.h"
#include "idt.h"

//array of pointers to our IRQ functions
void *irqRoutines[16] =
    {
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0
    };

//setup callback for particular IRQ
void irqInstallHandler(int irq, void (*handler)(struct regs *r))
{
  irqRoutines[irq] = handler;
}

//remove callback for particular IRQ
void irqUninstallHandler(int irq)
{
  irqRoutines[irq] = 0;
}


//IRQ from 0 to 7 were mapped to entries 8-19, now re re-map them to 32-47
void irqRemap(void)
{
  OUTb(0x20, 0x11);
  OUTb(0xA0, 0x11);
  OUTb(0x21, 0x20);
  OUTb(0xA1, 0x28);
  OUTb(0x21, 0x04);
  OUTb(0xA1, 0x02);
  OUTb(0x21, 0x01);
  OUTb(0xA1, 0x01);
  OUTb(0x21, 0x0);
  OUTb(0xA1, 0x0);
}

//install IRQ
void irqInstall()
{
  irqRemap();

  idtSetGate(32, (int64u) irq0, 0x08, 0x8E);
  idtSetGate(33, (int64u) irq1, 0x08, 0x8E);
  idtSetGate(34, (int64u) irq2, 0x08, 0x8E);
  idtSetGate(35, (int64u) irq3, 0x08, 0x8E);
  idtSetGate(36, (int64u) irq4, 0x08, 0x8E);
  idtSetGate(37, (int64u) irq5, 0x08, 0x8E);
  idtSetGate(38, (int64u) irq6, 0x08, 0x8E);
  idtSetGate(39, (int64u) irq7, 0x08, 0x8E);
  idtSetGate(40, (int64u) irq8, 0x08, 0x8E);
  idtSetGate(41, (int64u) irq9, 0x08, 0x8E);
  idtSetGate(42, (int64u) irq10, 0x08, 0x8E);
  idtSetGate(43, (int64u) irq11, 0x08, 0x8E);
  idtSetGate(44, (int64u) irq12, 0x08, 0x8E);
  idtSetGate(45, (int64u) irq13, 0x08, 0x8E);
  idtSetGate(46, (int64u) irq14, 0x08, 0x8E);
  idtSetGate(47, (int64u) irq15, 0x08, 0x8E);
}

//IRQs are pointing to this handler, instead to fault_handler. After we process request, we need to inform controller
//that request is processed, we do this by sending 0x20 to 2 chips. If IRQ is between 8 and 15 we must inform both of
// them, otherwise just hte first one
void irq_handler(struct regs *r)
{
  void (*handler)(struct regs *r);

  // if there is such handler, call it
  handler = irqRoutines[r->int_no - 32];
  if(handler)
  {
    handler(r);
  }

  // if IRQ is bigger than 8, inform 2nd controller at address 0xA0
  if(r->int_no >= 40)
  {
    OUTb(0xA0, 0x20);
  }

  OUTb(0x20, 0x20);
}
