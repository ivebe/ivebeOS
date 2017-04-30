/**
 * GDT - Global Descriptor Table - header file
 *
 * __attribute__((packed)) instruct compiler to not optimize this part of code,
 * because that can mess order of variables.
 *
 */

#pragma once
#include "stddef.h"

//structure that represent single entry in GDT table
struct gdtEntry
{
  int16u limit_low;
  int16u base_low;
  int8u base_middle;
  int8u access;
  int8u granularity;
  int8u base_high;
} __attribute__((packed));

//structure that represents pointer to GDT table
struct gdtPointer
{
  int16u limit;
  int32u base;
} __attribute__((packed));

extern void gdtFlush();
extern void gdtSetDescriptor(int32 num, int64u base, int64u limit, int8u access, int8u gran);
extern void gdtInstall();

