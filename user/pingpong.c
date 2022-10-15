#include "user/user.h"

int
main(int argc, char *argv[])
{
  char* buf = (char*)malloc(1);
  int p[2];
  pipe(p);

  write(p[1], "p", 1);
 
  int pid = fork();
  if (pid == 0) {
    read(p[0], buf, 1);
    
    int child = getpid();
    fprintf(1, "%d: received ping\n", child);

    write(p[1], "s", 1);
 
  } else {
    wait(0);
    read(p[0], buf, 1);
  
    int parent = getpid();
    fprintf(1, "%d: received pong\n", parent);
   
  }
 
  exit(0);
}
