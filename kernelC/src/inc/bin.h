/**
 * Binary files - header file
 *
 * Those functions will be considered as binary programs, since we haven't implemented reading ELF or similar files
 */


#pragma once
#include "stddef.h"
#include "system.h"

extern void detectCPU();
extern void detectCPUfeatures();
extern void cpuBench();
extern void reboot();
