#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int g = 100;

static void func(int a) {
    char *s1 = "abc";
    char *s2 = strdup(s1);
    int i1 = 3;
    int *i2 = &i1;
    static int i3 = 300;
    void *v1 = malloc(10);
    void *v2 = (void *)"abcdef";
    void *v3 = (void *)&i1;

    printf("param a is at %p\n", &a);
    printf("char *s1 is at %p which points to %p\n", &s1, s1);
    printf("char *s2 is at %p which points to %p\n", &s2, s2);
    printf("local var i1 is at %p\n", &i1);
    printf("local var i2 is at %p which points to %p\n", &i2, i2);
    printf("static var i3 is at %p\n", &i3);
    printf("void *v1 is at %p which points to %p\n", &v1, v1);
    printf("void *v2 is at %p which points to %p\n", &v2, v2);
    printf("void *v3 is at %p which points to %p\n", &v3, v3);
}

int main(int argc, char *argv[]) {
    printf("global var g is at %p\n", &g);
    func(4);
    printf("function func is at %p\n", &func);
    return 0;
}
