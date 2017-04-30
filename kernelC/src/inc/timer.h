/**
 * Time - header file
 */


#pragma once
#include "stddef.h"
#include "system.h"
#include "irq.h"

struct CLOCK
{
  int32u H;
  int32u M;
  int32u S;
  int32u mS;
};

extern void timerInstall();
extern void timer_handler(struct regs *r);
extern void printSysTime();
extern void printTime(struct CLOCK *t);
extern void getTimer(struct CLOCK *ret);
extern void startTimer();
extern void ticks2clock(int64u ticks, struct CLOCK *c);
extern int64u clock2ticks(struct CLOCK *c);
extern void subtract(struct CLOCK *a, struct CLOCK *b, struct CLOCK *c);
