// gcc -Wall sum8.c -o sum8
// ./sum5 4 8 -5 0 20
// prints: Sum=27 Sum2=505 Sum3=8451

#include <stdio.h>
#include <stdlib.h>

// sums[0] is sum, [1] is sum squares, [2] is sum cubes
static void sum8(int argc, char *argv[], int *sums) {
  sums[0] = 0;
  sums[1] = 0;
  sums[2] = 0;

  for (int i = 1; i < argc; i++) {
    int n = atoi(argv[i]);
    sums[0] += n;
    sums[1] += n * n;
    sums[2] += n * n * n;
  }
}

int main(int argc, char *argv[]) {
  int sums[3];  // sums[0] is sum, [1] is sum squares, [2] is sum cubes

  if (argc < 2) {
    printf("Usage: %s <list of numbers>\n", argv[0]);
    return 1;
  }

  sum8(argc, argv, sums);

  printf("Sum=%d Sum2=%d Sum3=%d\n", sums[0], sums[1], sums[2]);

  return 0;
}


