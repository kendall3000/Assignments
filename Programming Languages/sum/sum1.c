// gcc -Wall sum1.c -o sum1
// ./sum1 4 8 -5 0 20
// prints: Sum=27 Sum2=505 Sum3=8451

#include <stdio.h>
#include <stdlib.h>

static int sum1(int argc, char *argv[]) {
  int sum = 0;
  for (int i = 1; i < argc; i++) {
    int n = atoi(argv[i]);
    sum += n;
  }
  return sum;
}

static int sum2(int argc, char *argv[]) {
  int sumsq = 0;
  for (int i = 1; i < argc; i++) {
    int n = atoi(argv[i]);
    sumsq += n * n;
  }
  return sumsq;
}

static int sum3(int argc, char *argv[]) {
  int sumcube = 0;
  for (int i = 1; i < argc; i++) {
    int n = atoi(argv[i]);
    sumcube += n * n * n;
  }
  return sumcube;
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("Usage: %s <list of numbers>\n", argv[0]);
    return 1;
  }
  int x = sum1(argc, argv);
  int y = sum2(argc, argv);
  int z = sum3(argc, argv);
  printf("Sum=%d Sum2=%d Sum3=%d\n", x, y, z);
  return 0;
}
