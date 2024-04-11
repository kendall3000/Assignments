// gcc -Wall sum7.c -o sum7
// ./sum7 4 8 -5 0 20
// prints: Sum=27 Sum2=505 Sum3=8451

#include <stdio.h>
#include <stdlib.h>


#define sum7(argc, argv, x, y, z) \
  do { \
    x = 0; \
    y = 0; \
    z = 0; \
    for (int i = 1; i < argc; i++) { \
      int n = atoi(argv[i]); \
      x += n; \
      y += n * n; \
      z += n * n * n; \
    } \
  } while(0)

int main(int argc, char *argv[]) {
  int x, y, z;
  sum7(argc, argv, x, y, z);

  if (argc < 2) {
    printf("Usage: %s <list of numbers>\n", argv[0]);
    return 1;
  }

  printf("Sum=%d Sum2=%d Sum3=%d\n", x, y, z);

  return 0;
}

