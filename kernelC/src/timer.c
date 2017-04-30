/**
 * Time - source file
 */

#include "timer.h"
#include "vga.h"

struct CLOCK time;
struct CLOCK timerStart;
struct CLOCK current;

void subtract(struct CLOCK *a, struct CLOCK *b, struct CLOCK *c)
{
  int64u ticksA, ticksB;
  ticksA = clock2ticks(a);
  ticksB = clock2ticks(b);

  if(ticksA > ticksB) ticksA = ticksA - ticksB; //ticksA is difference between 2 measurements
  else ticksA = 0;

  ticks2clock(ticksA, c);
}

int64u clock2ticks(struct CLOCK *c)
{
  int64u ticks = 0;

  ticks += c->mS;
  ticks += c->S * 1000;
  ticks += c->M * 60 * 1000;
  ticks += c->H * 60 * 60 * 1000;

  return ticks;
}

void ticks2clock(int64u ticks, struct CLOCK *c)
{
  c->H = ticks / (60 * 60 * 1000);
  ticks %= (60 * 60 * 1000);
  c->M = ticks / (60 * 1000);
  ticks %= (60 * 1000);
  c->S = ticks / (1000);
  ticks %= (1000);
  c->mS = ticks;
}

// frequency of timer is 1193180Hz, we have to set divisor to some registers
void setTimerPhase(int hz)
{
  int divisor = 1193182 / hz;
  OUTb(0x43, 0x36);
  OUTb(0x40, divisor & 0xFF);
  OUTb(0x40, divisor >> 8);

}

// default rate is 18.222 times per second, we set it to 1ms in setTimerPhase(1000) -> 1000Hz = 1mS
void timer_handler(struct regs *r)
{
  time.mS++;

  if(time.mS >= 1000)
  {
    time.S++;
    time.mS = 0;
    if(time.S >= 60)
    {
      time.M++;
      time.S = 0;
      if(time.M >= 60)
      {
        time.H++;
        time.M = 0;
        if(time.H >= 24)
        {
          time.H = 0;
        }
      }
    }
  }
}

void startTimer()
{
  //we turn off interrupts until we get current time, then we turn them back on
  __asm__ __volatile__("cli");
  timerStart.H = time.H;
  timerStart.M = time.M;
  timerStart.S = time.S;
  timerStart.mS = time.mS;
  __asm__ __volatile__("sti");
}

void getTimer(struct CLOCK *ret)
{
  //we turn off interrupts until we get current time, then we turn them back on
  __asm__ __volatile__("cli");
  current.H = time.H;
  current.M = time.M;
  current.S = time.S;
  current.mS = time.mS;
  __asm__ __volatile__("sti");

  subtract(&current, &timerStart, ret);
}

void printSysTime()
{
  __asm__ __volatile__("cli");
  char *out = "";
  itoa(time.H, out);
  puts(out);
  putch(':');

  itoa(time.M, out);
  puts(out);
  putch(':');

  itoa(time.S, out);
  puts(out);
  putch('.');

  itoa(time.mS, out);
  puts(out);
  __asm__ __volatile__("sti");
}

void printTime(struct CLOCK *t)
{
  char _out[] = "";

  itoa(t->H, _out);
  puts(_out);

  putch(':');

  itoa(t->M, _out);
  puts(_out);

  putch(':');

  itoa(t->S, _out);
  puts(_out);

  putch(':');

  itoa(t->mS, _out);
  puts(_out);

  putch('\n');
}

void timerInstall()
{
  //Start time is 00:00:00.000
  time.H = 0;
  time.M = 0;
  time.S = 0;
  time.mS = 0;

  setTimerPhase(1000);

  //set timer_handler to IRQ0
  irqInstallHandler(0, timer_handler);
}
