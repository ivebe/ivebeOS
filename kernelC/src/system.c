/**
 * System functions C file
 */

#include "system.h"

//copy in memory
void *memcpy(void *dest, const void *src, size_t count)
{
  char *dest_p = (char *) dest;
  char *src_p = (char *) src;

  while (count--)
    *dest_p++ = *src_p++;

  return dest;
}

//write 32bit value to memory
void *memset(void *dest, int val, size_t count)
{
  char *dest_p = (char *) dest;
  unsigned char c = (unsigned char) val;

  while (count--)
    *dest_p++ = c;

  return dest;
}

//write 16bit value to memory
unsigned short *memsetw(unsigned short *dest, unsigned short val, size_t count)
{
  unsigned short *dest_p = (unsigned short *) dest;

  while (count--)
    *dest_p++ = val;

  return dest;
}

//return length of string
int32 strlen(const char *str)
{
  int count = 0;
  while (*str != '\0')
  {
    count++;
    str++;
  }

  return count;
}

//read byte from I/O location
unsigned char INb(unsigned short _port)
{
  unsigned char rv;
  __asm__ __volatile__ ("inb %1, %0" : "=a" (rv) : "Nd" (_port));
  return rv;
}

//write byte to I/O location
void OUTb(unsigned short _port, unsigned char _data)
{
  __asm__ __volatile__ ("outb %1, %0" : : "Nd" (_port), "a" (_data));
}

// char to int - works only for positive integers
int atoi(char *s)
{
  int size = strlen(s);
  int ret = 0;
  int i = 0;

  for (i = 0; i < size; i++)
  {
    if(s[i] >= '0' && s[i] <= '9')
      ret = ret * 10 + s[i] - 48;
    else
      return -1;
  }

  return ret;
}

// int to char
// Idea: find the number of digits in unt. Move pointer for that amount.
// Last character is '\0', we go from back and add digit by digit together with offset 48, which is actually
// ASCII for 0
void itoa(int i, char *out)
{
  //if it's 0 we return result right away
  if(i == 0)
  {
    *out = 48;
    *(out + 1) = '\0';
    goto end;
  }

  int numOfNums = 0;
  int inputNum = i;

  while (inputNum > 0)
  {
    numOfNums++;
    inputNum /= 10;
  }

  out += numOfNums;
  *out = '\0';
  out--;

  while (i > 0)
  {
    *out = (char) (i % 10 + 48);
    out--;
    i /= 10;
  }

  end:;
}

//compare n characters of 2 strings
int strncmp(const char *s1, const char *s2, int count)
{
  if(!count) return 0;

  int ret = 0;

  while (--count && *s1 && *s1 == *s2)
  {
    s1++;
    s2++;
  }

  ret = *(unsigned char *) s1 - *(unsigned char *) s2;

  if(ret > 0) ret = 1;
  if(ret < 0) ret = -1;

  return ret;
}

//compare 2 strings
int strcmp(const char *s1, const char *s2)
{
  int ret = 0;

  while (!(ret = *(unsigned char *) s1 - *(unsigned char *) s2) && *s2)
  {
    s1++;
    s2++;
  }

  if(ret < 0)
    ret = -1;
  else if(ret > 0)
    ret = 1;

  return ret;
}

//copy string from 2nd parameter to the end of string from 1st parameter
void strcat(char *to, const char *from)
{
  char *_to = to;
  const char *_from = from;

  //if(strlen(_to) >= 0)
  while (*_to != '\0') //...seek to the end...
    _to++;

  //...and then add 2nd parameter to end of first one
  if(strlen(_from) > 0)
    while (*_from != '\0')
      *(_to++) = *(_from++);

  *_to = '\0';
}