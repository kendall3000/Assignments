#ifndef _stack_h
#define _stack_h
#include <stdlib.h>
#include "booleanWithError.h"

typedef struct Stack
{
    char **data;            /* string data stored in the stack */
    int top;                /* index of the last element in the array */
    int capacity;           /* current capacity of stack */
} Stack;

Stack *createStack( );
void freeStack( Stack *ps );
void freeStackElements( Stack *ps  );

char *pop( Stack *ps );
void push( Stack *ps, char *str );
char *top( Stack *ps );

boolean isEmpty( Stack *ps );
boolean isFull( Stack *ps );

#endif