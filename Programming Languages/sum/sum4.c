// gcc -Wall sum4.c -o sum4
// ./sum4 4 8 -5 0 20
// prints: Sum=27 Sum2=505 Sum3=8451

#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int x;   // Sum
  int y;   // Sum squares
  int z;   // Sum cubes
} sum_t;

static void sum4(int argc, char *argv[], sum_t *sum) {
  sum->x = 0;
  sum->y = 0;
  sum->z = 0;

  for (int i = 1; i < argc; i++) {
    int n = atoi(argv[i]);
    sum->x += n;
    sum->y += n * n;
    sum->z += n * n * n;
  }
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("Usage: %s <list of numbers>\n", argv[0]);
    return 1;
  }

  sum_t m;
  sum4(argc, argv, &m);

  printf("Sum=%d Sum2=%d Sum3=%d\n", m.x, m.y, m.z);

  return 0;
}
