#ifndef _point2D_h
#define _point2D_h
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct Point2D
{
    int x;
    int y;
}  Point2D;

bool equals( Point2D p1, Point2D p2 );
Point2D createPoint( int x, int y );
long getKey( Point2D p );

#endif
