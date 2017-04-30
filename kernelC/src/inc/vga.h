/**
 * VGA header file
 *
 * Value 	Color 	    Value 	Color
 * 0       	BLACK 	    8 	    DARK GREY
 * 1 	    BLUE 	    9 	    LIGHT BLUE
 * 2 	    GREEN 	    10 	    LIGHT GREEN
 * 3 	    CYAN 	    11 	    LIGHT CYAN
 * 4 	    RED 	    12 	    LIGHT RED
 * 5 	    MAGENTA 	13 	    LIGHT MAGENTA
 * 6 	    BROWN 	    14 	    LIGHT BROWN
 * 7 	    LIGHT GREY 	15 	    WHITE
 */

#pragma once
#include "stddef.h"
#include "system.h"

#ifndef BLACK
#define BLACK           0x00
#endif

#ifndef BLUE
#define BLUE            0x01
#endif

#ifndef GREEN
#define GREEN           0x02
#endif

#ifndef CYAN
#define CYAN            0x03
#endif

#ifndef RED
#define RED             0x04
#endif

#ifndef MAGENTA
#define MAGENTA         0x05
#endif

#ifndef BROWN
#define BROWN           0x06
#endif

#ifndef LIGHT_GREY
#define LIGHT_GREY      0x07
#endif

#ifndef DARK_GREY
#define DARK_GREY       0x08
#endif

#ifndef LIGHT_BLUE
#define LIGHT_BLUE      0x09
#endif

#ifndef LIGHT_GREEN
#define LIGHT_GREEN     0x0A
#endif

#ifndef LIGHT_CYAN
#define LIGHT_CYAN      0x0B
#endif

#ifndef LIGHT_RED
#define LIGHT_RED       0x0C
#endif

#ifndef LIGHT_MAGENTA
#define LIGHT_MAGENTA   0x0D
#endif

#ifndef LIGHT_BROWN
#define LIGHT_BROWN     0x0E
#endif

#ifndef WHITE
#define WHITE           0x0F
#endif

extern void scrollDown(void);
extern void moveCursor(void);
extern void cls();
extern void putch(unsigned char c);
extern void puts(char *text);
extern void setColor(unsigned char foreground, unsigned char background);
extern void initVGA(void);
extern void putsR(char *text);
extern void putnch(char c, int n);
