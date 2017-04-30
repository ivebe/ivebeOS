/**
 * ivebeOS Kernel v0.2
 */

#include "vga.h"
#include "idt.h"
#include "gdt.h"
#include "isr.h"
#include "io.h"
#include "irq.h"
#include "timer.h"
#include "kb.h"
#include "system.h"

void k_main(void)
{
  initVGA();

  char *gdsStr = "Setting GDT table ";
  char *idtStr = "Setting IDT table ";
  char *isrStr = "Setting ISR-a ";
  char *irqStr = "Setting IRQ handler ";
  char *timerStr = "Initialize timer ";
  char *keyboardStr = "Initialize keyboard ";
  char *stiStr = "Enable interrupts ";

  setColor(RED, WHITE);
  puts("Welcome to ivebeOS v0.2.\n");
  setColor(BLACK, WHITE);

  setColor(DARK_GREY, WHITE);
  puts("Kernel loaded, loading rest of the components...\n\n");
  setColor(BLACK, WHITE);

  puts(gdsStr);
  putnch('.', 80 - strlen(gdsStr) - 5); //80 is length of line - string - length of string " DONE"

  gdtInstall();

  setColor(GREEN, WHITE);
  putsR(" DONE");
  setColor(BLACK, WHITE);

  puts(idtStr);
  putnch('.', 80 - strlen(idtStr) - 5); //80 is length of line - string - length of string " DONE"

  idtInstall();

  setColor(GREEN, WHITE);
  putsR(" DONE");
  setColor(BLACK, WHITE);

  puts(isrStr);
  putnch('.', 80 - strlen(isrStr) - 5); //80 is length of line - string - length of string " DONE"

  isrInstall();

  setColor(GREEN, WHITE);
  putsR(" DONE");
  setColor(BLACK, WHITE);

  puts(irqStr);
  putnch('.', 80 - strlen(irqStr) - 5); //80 is length of line - string - length of string " DONE"

  irqInstall();

  setColor(GREEN, WHITE);
  putsR(" DONE");
  setColor(BLACK, WHITE);

  puts(stiStr);
  putnch('.', 80 - strlen(stiStr) - 5); //80 is length of line - string - length of string " DONE"

  __asm__ __volatile__("sti"); //interrupts ON

  setColor(GREEN, WHITE);
  putsR(" DONE");
  setColor(BLACK, WHITE);

  puts(timerStr);
  putnch('.', 80 - strlen(timerStr) - 5); //80 is length of line - string - length of string " DONE"

  timerInstall();

  setColor(GREEN, WHITE);
  putsR(" DONE");
  setColor(BLACK, WHITE);

  puts(keyboardStr);
  putnch('.', 80 - strlen(keyboardStr) - 5); //80 is length of line - string - length of string " DONE"

  keyboardInstall();

  setColor(GREEN, WHITE);
  putsR(" DONE");
  setColor(BLACK, WHITE);

  setColor(DARK_GREY, WHITE);
  puts("\nFor list of commands enter HELP. NOTE: capital letters are not supported!\n\n");
  setColor(BLACK, WHITE);

  prompt();
}
