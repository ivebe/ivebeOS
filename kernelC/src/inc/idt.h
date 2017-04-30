/**
 * IDT - Interrupt Descriptor Table - header file
 */

#pragma once
#include "stddef.h"

//structure for IDT entry
struct idtEntry
{
  int16u base_lo;
  int16u sel;
  int8u always0;
  int8u flags;
  int16u base_hi;
} __attribute__((packed));

//pointer to IDT
struct idtPointer
{
  int16u limit;
  int32u base;
} __attribute__((packed));

extern void idtLoad();
extern void idtSetGate(int8u num, int64u base, int16u sel, int8u flags);
extern void idtInstall();
