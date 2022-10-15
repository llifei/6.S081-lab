#include "user/user.h"
#include "kernel/stat.h"
#include "kernel/fs.h"

void find(char *path, char *model) {
  
  int fd;
  struct stat st;
  char buf[512], *p;
  struct dirent de;

  if ((fd = open(path, 0)) < 0) {
    fprintf(2, "find: cannot open %s\n", path);
    return;
  }

  if (fstat(fd, &st) < 0) {
    fprintf(2, "find: cannot stat %s\n", path);
    close(fd);
    return;
  }

  switch(st.type) {
    
    case T_FILE:
      fprintf(2, "find: %s is not a directory\n", path);
      break;
    
    case T_DIR:
      if (strlen(path) + 1 + DIRSIZ + 1 > sizeof buf) {
        fprintf(2, "find: path is too long\n");
	break;
      }
    strcpy(buf, path);
    p = buf + strlen(buf);
    *p++ = '/';
    while (read(fd, &de, sizeof(de)) == sizeof(de)) {
      if (de.inum == 0)
        continue;
      memmove(p, de.name, DIRSIZ);
      p[DIRSIZ] = 0;
      if (stat(buf, &st) < 0) {
        fprintf(2, "find: cannot stat %s\n", buf);
	continue;
      }

      switch(st.type) {

        case T_DIR:
	  if (strcmp(p, ".") != 0 && strcmp(p, "..") != 0) {
	    find(buf, model);
	  }
	  break;

	case T_FILE:
	  if (strcmp(de.name, model) == 0) {
	    fprintf(1, "%s\n", buf);
	  }
	  break;
      }
    }
  }
  close(fd);
}


int main(int argc, char *argv[]) {

  if (argc != 3) {
    fprintf(2, "find: the number of arguments should be 2, but now is %d.\n", argc);
    exit(1);
  }

  char *path = argv[1];
  char *model = argv[2];
  
  find(path, model);


  exit(0);
}
