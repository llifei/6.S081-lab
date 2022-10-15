#include "user/user.h"

int isPrime(int num) {
  for (int i = 2; i * i < num; i++) {
    if (num % i == 0) {
      return 0;
    }
  }
  return 1;
}

void process(int p[]) {

  int prime;

  read(p[0], &prime, 4);
  fprintf(1, "prime %d\n", prime++);
  close(p[0]);
  
  while (prime <= 35 && isPrime(prime) == 0) {
    prime++;
  }
  if (prime > 35) {
    exit(0);
  }
  int new_p[2];
  pipe(new_p);
  write(new_p[1], &prime, 4);
  close(new_p[1]);

  if (fork() == 0) {

    process(p);
    exit(0);

  } else {
    wait(0);
    exit(0);
  }

}


int main(int argc, char *argv[]) {
  
  int p[2];
  pipe(p);
  int first = 2;
  while (first <= 35 && isPrime(first) == 0) {
    first++;
  }
  write(p[1], &first, 4);
  close(p[1]);
  process(p);


  exit(0);
}
