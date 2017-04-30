/**
 * Binary files - source file
 */

#include "bin.h"
#include "vga.h"
#include "timer.h"

#define CPUID(in, eax, ebx, ecx, edx) __asm__("cpuid": "=a" (eax), "=b" (ebx), "=c" (ecx), "=d" (edx) : "a" (in));

void detectCPU()
{
  int32u eax, ebx, ecx, edx;
  char id[13];

  CPUID(0x00, eax, ebx, ecx, edx);

  // String is in register ebx + edx + ecx, in reverse order.
  // Ex. "GenuineIntel" looks like: EBX = uneG, ECX = letn, EDX = Ieni

  id[0] = ebx >> 0;
  id[1] = ebx >> 8;
  id[2] = ebx >> 16;
  id[3] = ebx >> 24;

  id[4] = edx >> 0;
  id[5] = edx >> 8;
  id[6] = edx >> 16;
  id[7] = edx >> 24;

  id[8] = ecx >> 0;
  id[9] = ecx >> 8;
  id[10] = ecx >> 16;
  id[11] = ecx >> 24;

  id[12] = '\0';

  puts("\nCPU Type: ");
  puts(id);
}

void detectCPUfeatures()
{
  /*
    bit (edx) 	feature
    18			PN
    19			CLFlush
    23			MMX
    25			SSE
    26			SSE2
    28			HTT
    */

  int32u eax, ebx, ecx, edx;
  CPUID(0x01, eax, ebx, ecx, edx);

  //PN
  puts("\nPN supported: ");
  putnch(' ', 20 - strlen("PN supported: "));
  if((edx & 0x00020000) >> 17 == 1)
  {
    setColor(GREEN, WHITE);
    puts("YES");
  }
  else
  {
    setColor(LIGHT_RED, WHITE);
    puts("NO");
  }
  setColor(BLACK, WHITE);

  //CLFlush
  puts("\nCLFlush supported: ");
  putnch(' ', 20 - strlen("CLFlush supported: "));
  if((edx & 0x00040000) >> 18 == 1)
  {
    setColor(GREEN, WHITE);
    puts("YES");
  }
  else
  {
    setColor(LIGHT_RED, WHITE);
    puts("NO");
  }
  setColor(BLACK, WHITE);

  //MMX
  puts("\nMMX supported: ");
  putnch(' ', 20 - strlen("MMX supported: "));
  if((edx & 0x00400000) >> 22 == 1)
  {
    setColor(GREEN, WHITE);
    puts("YES");
  }
  else
  {
    setColor(LIGHT_RED, WHITE);
    puts("NO");
  }
  setColor(BLACK, WHITE);

  //SSE
  puts("\nSSE supported: ");
  putnch(' ', 20 - strlen("SSE supported: "));
  if((edx & 0x01000000) >> 24 == 1)
  {
    setColor(GREEN, WHITE);
    puts("YES");
  }
  else
  {
    setColor(LIGHT_RED, WHITE);
    puts("NO");
  }
  setColor(BLACK, WHITE);

  //SSE2
  puts("\nSSE2 supported: ");
  putnch(' ', 20 - strlen("SSE2 supported: "));
  if((edx & 0x02000000) >> 25 == 1)
  {
    setColor(GREEN, WHITE);
    puts("YES");
  }
  else
  {
    setColor(LIGHT_RED, WHITE);
    puts("NO");
  }
  setColor(BLACK, WHITE);

  //HTT
  puts("\nHTT supported: ");
  putnch(' ', 20 - strlen("HTT supported: "));
  if((edx & 0x08000000) >> 27 == 1)
  {
    setColor(GREEN, WHITE);
    puts("YES");
  }
  else
  {
    setColor(LIGHT_RED, WHITE);
    puts("NO");
  }
  setColor(BLACK, WHITE);

  //SSE3 - bit0 ecx
  puts("\nSSE3 supported: ");
  putnch(' ', 20 - strlen("SSE3 supported: "));
  if((ecx & 0x01) == 1)
  {
    setColor(GREEN, WHITE);
    puts("YES");
  }
  else
  {
    setColor(LIGHT_RED, WHITE);
    puts("NO");
  }
  setColor(BLACK, WHITE);
}

void cpuBench()
{
  puts("\nCPU benchmark is processing 900,000,000 iteration of each operation\nand showing how long did it take\n");
  puts("\nCPU benchmark started, please wait...");
  int iteration = 900000000; //900 million
  int i = iteration;
  int test = 0;
  double doubleTest = 0.0;
  struct CLOCK benchResult;

  //test++
  startTimer();
  while (i-- > 0)
  {
    test++;
  }
  getTimer(&benchResult);
  puts("\nExecution time of adding operation (i++): ");

  setColor(BLUE, WHITE);
  printTime(&benchResult);
  setColor(BLACK, WHITE);
  i = iteration;
  test = 0;

  //multiplying
  startTimer();
  while (i-- > 0)
  {
    test *= 32000;
  }
  getTimer(&benchResult);
  puts("Execution time of multiplying operation: ");

  setColor(BLUE, WHITE);
  printTime(&benchResult);
  setColor(BLACK, WHITE);
  i = iteration;
  test = 0;

  //dividing
  startTimer();
  while (i-- > 0)
  {
    test /= 32000;
  }
  getTimer(&benchResult);
  puts("Execution time of dividing operation: ");

  setColor(BLUE, WHITE);
  printTime(&benchResult);
  setColor(BLACK, WHITE);
  i = iteration;
  test = 0;

  //subtraction
  startTimer();
  while (i-- > 0)
  {
    test -= 32000;
  }
  getTimer(&benchResult);
  puts("Execution time of subtraction operation: ");

  setColor(BLUE, WHITE);
  printTime(&benchResult);
  setColor(BLACK, WHITE);
  i = iteration;
  test = 0;

  //mod
  startTimer();
  while (i-- > 0)
  {
    test %= 32000;
  }
  getTimer(&benchResult);
  puts("Execution time of module operation (i%n): ");

  setColor(BLUE, WHITE);
  printTime(&benchResult);
  setColor(BLACK, WHITE);
  i = iteration;
  test = 0;

  //double add
  startTimer();
  while (i-- > 0)
  {
    doubleTest += 32.0;
  }
  getTimer(&benchResult);
  puts("Execution time of adding double variable operation: ");

  setColor(BLUE, WHITE);
  printTime(&benchResult);
  setColor(BLACK, WHITE);
  i = iteration;
  doubleTest = 0.0;

  //double add, two times
  startTimer();
  while (i-- > 0)
  {
    doubleTest += 23.0;
    doubleTest += 32.0;
  }
  getTimer(&benchResult);
  puts("Execution time of adding 2 double variable operation: ");

  setColor(BLUE, WHITE);
  printTime(&benchResult);
  setColor(BLACK, WHITE);
  i = iteration;
  doubleTest = 0.0;

  //double dividing
  startTimer();
  while (i-- > 0)
  {
    doubleTest /= 32.0;
  }
  getTimer(&benchResult);
  puts("Execution time of dividing with double variable operation: ");

  setColor(BLUE, WHITE);
  printTime(&benchResult);
  setColor(BLACK, WHITE);
  i = iteration;
  doubleTest = 0.0;
}

void reboot()
{
  __asm__ ("cli");
  int temp;

  do
  {
    temp = INb(0x64);
    if(temp & 1) INb(0x60);
  } while (temp & 2);

  // Restart
  OUTb(0x64, 0xFE);
}
