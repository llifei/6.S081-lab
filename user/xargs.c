#include "user/user.h"


char* readLine(char *p) {

  while (read(0, p, 1) > 0) {
    if (*p == '\n') {
      *p = '\0';
      return p;
    }
    p++;
  }
  *p = '\0';
  return p;
}


void process(char *p, char *line, int argc, char *argv[]) {


  if (fork() == 0) {
    char *exec_argv[argc + 1];
    for (int i = 0; i < argc; i++) {
      exec_argv[i] = argv[i];
    }
    *(exec_argv + argc) = line;
    exec(argv[0], exec_argv);
    fprintf(2,  "xargs: exec %s failed\n", argv[0]);
    exit(1);
  } else {
    wait(0);
    line = p;
    p = readLine(p);
    if (*line != '\0') {
      process(p, line, argc, argv);
    }
  }

}


int main (int argc, char *argv[]) {

  char buf[1000];
  char *p = buf;

  readLine(p);

  process(p, buf, argc - 1, argv + 1);

  exit(0);
}
