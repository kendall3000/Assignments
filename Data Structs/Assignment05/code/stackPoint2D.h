#ifndef _stackPoint2D_h
#define _stackPoint2D_h
#include <stdlib.h>
#include <stdbool.h>

#include "point2D.h"

typedef Point2D stackType; //Change this line to set the type for the stack to store

typedef struct Stack
{
    stackType *data;        //stackType data stored in the stack
    int top;                //index of the last element in the array
    int capacity;           //current capacity of stack
} Stack;

Stack *createStack( );
void freeStack( Stack *ps );
//void freeStackElements( Stack *ps  );

stackType pop( Stack *ps );
void push( Stack *ps, stackType st );
stackType top( Stack *ps );

bool isEmptyStack( Stack *ps );
bool isFullStack( Stack *ps );

#endif
