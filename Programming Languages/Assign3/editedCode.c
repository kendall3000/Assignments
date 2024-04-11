#include <stdio.h>

static int a = 10;
static int b = 20;
static int c = 30;

static void f(int *a_ptr, int *b_ptr, int *c_ptr) {
    (*a_ptr) += 5;
    (*b_ptr) += 5;
    (*c_ptr) += 3;
    printf("f: a=%d b=%d c=%d\n", *a_ptr, *b_ptr, *c_ptr);
}

static void g(int *a_ptr, int *b_ptr, int *c_ptr) {
    int local_c = 40;
    (*b_ptr) += 5;
    local_c += 5;
    f(a_ptr, b_ptr, &local_c);
    printf("g: a=%d b=%d c=%d\n", *a_ptr, *b_ptr, local_c);
}

int main(int argc, char *argv[]) {
    g(&a, &b, &c);
    printf("main: a=%d b=%d c=%d\n", a, b, c);
}
