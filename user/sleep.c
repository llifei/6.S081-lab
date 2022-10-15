#include "user/user.h"
#include "kernel/types.h"

int
main(int argc, char *argv[])
{
  if (argc == 1)
  {
    fprintf(1, "sleep: no arguments error.\n");
    exit(1);
  }

  if (argc > 2)
  {
    fprintf(1, "sleep: number of argument should be 1, not %d.\n", argc - 1);
    exit(1);
  }

  int ticks = atoi(argv[1]);
  
  sleep(ticks);

  exit(0);
}
