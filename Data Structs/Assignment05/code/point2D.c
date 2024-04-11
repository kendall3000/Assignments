#include <limits.h>
#include "point2D.h"

bool equals( Point2D p1, Point2D p2 ){
    return (p1.x==p2.x)&&(p1.y==p2.y);
}

Point2D createPoint( int x, int y ){
    Point2D p;
    p.x = x;
    p.y = y;

    return p;
}

long getKey( Point2D p ){
    long key = p.x;
    key += (long)p.y<<16;
    return key;
}
