#ifndef _array2D_h
#define _array2D_h
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "color.h"

typedef struct array2D
{
    int length;
    int width;
    char** array2D;
}  array2D;

array2D* mallocArray2D( int length, int width );
void printArray2D( array2D* arrayData, bool enabled );
void freeArray2D( array2D* arrayData );

#endif
