#include "user/user.h"
#include "kernel/types.h"
#include "kernel/param.h"
#include "kernel/stat.h"

int main(int argc, char *argv[]) {
 
  char *arguments[] = {"echo", "hello"};
  exec(arguments[0] , arguments);
  fprintf(2, "exec: echo failed\n");

  exit(1);
}
