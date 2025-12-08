// spawn.c
#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char *argv[])
{
  int n = 6;   // we'll create 6 children: 2 of each "state type"

  printf(1, "spawn: creating %d children (2 sleepers, 2 hogs, 2 zombies)\n", n);

  for (int i = 0; i < n; i++) {
    int pid = fork();
    if (pid < 0) {
      printf(1, "spawn: fork failed\n");
      exit();
    }

    if (pid == 0) {
      // CHILD BEHAVIOR
      if (i < 2) {
        // 0,1 → SLEEPING processes
        while (1) {
          sleep(200);   // mostly SLEEPING
        }
      } else if (i < 4) {
        // 2,3 → CPU hogs (RUNNING/RUNNABLE)
        volatile int x = 0;
        while (1) {
          x++;          // burn CPU, rarely sleeping
        }
      } else {
        // 4,5 → ZOMBIE processes: exit immediately
        exit();
      }
      // never reached
    }

    // PARENT: just continues loop to fork next child
  }

  // Parent stays alive and NEVER calls wait() -> children 4 and 5 stay ZOMBIE
  while (1) {
    sleep(1000);
  }

  exit();
}
