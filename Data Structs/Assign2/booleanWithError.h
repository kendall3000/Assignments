#ifndef _booleanWithError_h
#define _booleanWithError_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum boolean { FALSE, TRUE, ERROR } boolean;

boolean strequals( char *str1, char *str2 );
boolean stringToBoolean( char *str );
char *booleanToString( boolean b );

#endif