#include <limits.h>
#include "point2D.h"

/* equals
 * input: 2 Point2Ds
 * output: a bool
 *
 * Return true if the Point2Ds have the same x and y values.  Otherwise return false.
 */
bool equals( Point2D p1, Point2D p2 ){
    return (p1.x==p2.x)&&(p1.y==p2.y);
}

/* createPoint
 * input: 2 ints
 * output: a Point2D
 *
 * Create a Point2D with the specified x and y coordinates.
 */
Point2D createPoint( int x, int y ){
    Point2D p;
    p.x = x;
    p.y = y;

    return p;
}

/* getKey
 * input: a Point2D
 * output: long
 *
 * Convert a Point2D to a unique long value.  This long can be used as a key to insert into a hash table.
 */
long getKey( Point2D p ){
    long key = p.x;
    key += (long)p.y*INT_MAX;
    return key;
}
