/**
 * Keyboard header
 */
 
#pragma once
#include "stddef.h"
#include "system.h"
#include "irq.h"

extern void keyboard_handler(struct regs *r);
extern void keyboardInstall();

