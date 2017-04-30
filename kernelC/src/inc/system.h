/**
 * System functions H file
 */

#pragma once
#include "stddef.h"

extern void *memcpy(void *dest, const void *src, size_t count);
extern void *memset(void *dest, int val, size_t count);
extern unsigned short *memsetw(unsigned short *dest, unsigned short val, size_t count);
extern int32 strlen(const char *str);
extern unsigned char INb(unsigned short _port);
extern void OUTb(unsigned short _port, unsigned char _data);
extern int atoi(char *s);
extern void itoa(int i, char *out);
extern int strncmp(const char *s1, const char *s2, int count);
extern int strcmp(const char *s1, const char *s2);
extern void strcat(char *_to, const char *_from);

//stack after ISR
struct regs
{
  unsigned int gs, fs, es, ds;                           // push - last segments
  unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;   // push - 'pusha'
  unsigned int int_no, err_code;                         // 'push byte #' and error_code
  unsigned int eip, cs, eflags, useresp, ss;             // push - automatic by CPU
};
