/**
 * System functions C file
 *
 * Version: 0.1
 */

#include "timer.h"
#include "vga.h"
#include "io.h"

//US Keyboard Layout.
unsigned char kb_layout_US_small[128] =
{
    0, 27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
    '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',    /* Enter key */
    0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',
    0, '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0, /* Right shift */
    '*',
    0,    /* Alt */
    ' ',    /* Space bar */
    0,    /* Caps lock */
    0,    /* 59 - F1 key ... > */
    0, 0, 0, 0, 0, 0, 0, 0,
    0,    /* < ... F10 */
    0,    /* 69 - Num lock*/
    0,    /* Scroll Lock */
    0,    /* Home key */
    0,    /* Up Arrow */
    0,    /* Page Up */
    '-',
    0,    /* Left Arrow */
    0,
    0,    /* Right Arrow */
    '+',
    0,    /* 79 - End key*/
    0,    /* Down Arrow */
    0,    /* Page Down */
    0,    /* Insert Key */
    0,    /* Delete Key */
    0, 0, 0,
    0,    /* F11 Key */
    0,    /* F12 Key */
    0,    /* All other keys are undefined */
};

char *buffer = "";
int length = 0;
char c;

// handler for processing pressed key
void keyboard_handler(struct regs *r)
{
  unsigned char scancode;

  //read from keyboard buffer
  scancode = INb(0x60);

  //if key is released
  if(!(scancode & 0x80))
  {
    c = kb_layout_US_small[scancode];

    if(c == '\n')
    {
      *(buffer + length) = '\0';
      length = 0;
      exec(buffer);
    }
    else
    {
      *(buffer + length++) = c;
      putch(c);
    }
  }
}

/* Setup keyboard handler to IRQ1 */
void keyboardInstall()
{
  irqInstallHandler(1, keyboard_handler);
}
