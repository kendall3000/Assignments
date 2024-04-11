#ifndef _paintRoom_h
#define _paintRoom_h

#include <stdlib.h>
#include <stdio.h>

/* DO NOT MODIFY THIS FILE */

typedef struct RoomData
{
    char **roomArray;      /* the 2d char array representing the room shared by Jethro and Cletus */
    int numrows;           /* the number of rows for the char** roomArray */
    int numcols;           /* the number of columns for the char** roomArray */
} RoomData;

void printName( );
void paintRoom( RoomData room );

#endif