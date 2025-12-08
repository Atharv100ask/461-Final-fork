// uproc.h – shared process info struct for getprocs()

#ifndef UPROC_H
#define UPROC_H

#include "types.h"

struct uproc {
  int pid;
  char name[16];
  int state;
  uint sz;         // memory size in bytes
  uint cpu_ticks;  // number of timer ticks this process has run
};

#endif
