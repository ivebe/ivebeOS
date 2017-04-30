/**
 * I/O source file
 */

#include "io.h"
#include "vga.h"
#include "timer.h"
#include "bin.h"

char *promptTxt = "\nCONSOLE: ";
char *errorTxt = "UNKNOWN COMMAND";

void prompt()
{
  setColor(GREEN, WHITE);
  puts(promptTxt);
  setColor(BLACK, WHITE);
}

void printError()
{
  setColor(LIGHT_RED, WHITE);
  puts(errorTxt);
  setColor(BLACK, WHITE);
}

void exec(char *buffer)
{
  //Internal commands like echo, help, cls...

  if(strncmp(buffer, "echo ", 5) == 0)
  {
    putch('\n');
    puts(buffer + 5);
  }
  else if(strcmp(buffer, "help") == 0)
  {
    putch('\n');

    puts("#1: HELP   - List of commands and their description\n");
    puts("#2: ECHO   - Output text to terminal\n");
    puts("#3: TIME   - Time since system booted\n");
    puts("#4: CLS    - Clear screen\n");
    puts("#5: CLEAR  - Clear screen (alias to CLS)\n");
    puts("#6: BENCH  - Run CPU benchmark\n");
    puts("#7: CPUID  - Identify CPU-a\n");
    puts("#8: EXIT   - Restart system\n");
    puts("#9: ABOUT  - Few words about ivebe OS");
  }
  else if(strcmp(buffer, "about") == 0)
  {
    puts("\nivebeOS is amateur OS created for exam at Technical Faculty Cacak, Serbia,\n");
    puts("by Danijel Petrovic. ");
    puts("I recently found source on some old drive and decided\n");
    puts("to translate code comments to English and publish the code.\n");
    puts("Some parts of code are collected from different sources,\n");
    puts("I'm attributing them in no particular order.\n");
    puts("(if someone is forgotten, let me know and I'll gladly add you to the list):\n\n");
    puts("- http://wiki.osdev.org\n- http://www.osdever.net (Brandon Friesen)\n");
  }
  else if(strcmp(buffer, "time") == 0)
  {
    putch('\n');
    printSysTime();
  }
  else if(strcmp(buffer, "cls") == 0 || strcmp(buffer, "clear") == 0)
  {
    cls();
  }
  else if(strcmp(buffer, "bench") == 0)
  {
    cpuBench();
  }
  else if(strcmp(buffer, "cpuid") == 0)
  {
    putch('\n');
    detectCPU();
    putch('\n');
    detectCPUfeatures();
  }
  else if(strcmp(buffer, "exit") == 0)
  {
    reboot();
  }
  else
  {
    putch('\n');
    printError();
  }

  prompt();
}
