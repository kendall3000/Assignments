#include "booleanWithError.h"

/* strequals
 * input: two strings
 * output: boolean
 *
 * Returns ERROR if either of strings are NULL.
 * Returns TRUE if the strings are equal.
 * Returns FALSE if the strings are not equal.
 */
boolean strequals( char *str1, char *str2 ){
    if( str1 == NULL || str2 == NULL ){
        return ERROR;
    }
    return !strcmp( str1, str2 );
}

/* stringToBoolean
 * input: a string
 * output: boolean
 *
 * Returns TRUE if the string is "T".
 * Returns FALSE if the string is "F".
 * Returns ERROR otherwise (including if the string is NULL).
 */
boolean stringToBoolean( char *str ){
    boolean b;

    if( str==NULL ){
        b = ERROR;
    }
    else if( strequals( str, "T" ) ){
        b = TRUE;
    }
    else if( strequals( str, "F" ) ){
        b = FALSE;
    }
    else{
        b = ERROR;
    }

    return b;
}

/* booleanToString
 * input: a boolean
 * output: a string (this is malloc-ed so must be freed eventually!)
 *
 * Returns "T" if the boolean is TRUE.
 * Returns "F" if the boolean is FALSE.
 * Returns ERROR otherwise.
 */
char *booleanToString( boolean b ){
    char *str = (char *)malloc( sizeof(char)*2 );
    str[1] = '\0';

    if( b == TRUE ){
        str[0] = 'T';
    }
    else if( b == FALSE ){
        str[0] = 'F';
    }
    else{
        str[0] = 'E';
    }

    return str;
}