/**
 * VGA - source file
 */

#include "vga.h"

//16bit video memory pointer
int16u *vidmem;

//default color is black adn white
int16u color = 0x0F;

//cursor position 0,0
int32u x = 0, y = 0;

//write char to screen
void putch(unsigned char c)
{
  int16u *vidmem_position;

  //backspace
  if(c == 0x08)
  {
    if(x != 0) x--;
  }

  //tab
  else if(c == 0x09)
  {
    if(x + 4 <= 80)
      x += 4;
  }
  //'Carriage Return', move cursor to start of line
  else if(c == '\r')
  {
    x = 0;
  }
  //new line
  else if(c == '\n')
  {
    x = 0;
    y++;
  }
  // indexInMemory = (y * width) + x
  else if(c >= ' ')
  {
    vidmem_position = vidmem + (y * 80 + x);
    *vidmem_position = c | color;
    x++;
  }

  if(x >= 80)
  {
    x = 0;
    y++;
  }

  scrollDown();
  moveCursor();
}

//write string on screen
void puts(char *text)
{
  int i;
  int length = strlen((const char *) text);

  for (i = 0; i < length; i++)
  {
    putch(text[i]);
  }
}

//write string on the right side of screen
void putsR(char *text)
{
  int length = strlen(text);

  int16u *vidmem_position;

  x = 80 - length;

  while (*text != '\0')
  {
    vidmem_position = vidmem + (y * 80 + x);
    *vidmem_position = *text | color;
    text++;
    x++;
  }
  x = 0;
  y++;

  scrollDown();
  moveCursor();

}

//write character N times
void putnch(char c, int n)
{

  int16u *vidmem_position;

  while (n-- > 0)
  {
    vidmem_position = vidmem + (y * 80 + x);
    *vidmem_position = c | color;
    x++;

    if(x >= 80)
    {
      x = 0;
      y++;
    }
  }

  scrollDown();
  moveCursor();

}

//setup foreground/background color
void setColor(unsigned char foreground, unsigned char background)
{
  color = (background << 4) | (foreground & 0x0F);
  color = color << 8;
}

//remove all text from screen
void cls()
{
  unsigned short blank;
  unsigned int i;

  blank = 0x20 | color;

  for (i = 0; i < 25; i++)
    memsetw(vidmem + i * 80, blank, 80);

  x = 0;
  y = 0;
  moveCursor();
}

//move cursor
void moveCursor(void)
{
  size_t temp;

  //indexInMemory = y * width + x
  temp = y * 80 + x;

  //setup cursor in hardware registry. Screen is 80x25, so we need 2 8bit registry
  //15 is LSB, and 14 is MSB
  OUTb(0x3D4, 14);
  OUTb(0x3D5, (unsigned char) (temp >> 8));
  OUTb(0x3D4, 15);
  OUTb(0x3D5, (unsigned char) (temp));
}

//scroll screen down, is actually move everything up for one line
void scrollDown(void)
{
  unsigned short blank, temp;

  //blank
  blank = 0x20 | color;

  if(y >= 25)
  {
    //copy everything from 2nd row for one up
    temp = y - 25 + 1;
    memcpy(vidmem, vidmem + temp * 80, (25 - temp) * 80 * 2);

    //fill last row with blank
    memsetw(vidmem + (25 - temp) * 80, blank, 80);
    y = 24;
  }
}

void initVGA(void)
{
  vidmem = (int16u *) 0xB8000;
  setColor(BLACK, WHITE);
  cls();
}
