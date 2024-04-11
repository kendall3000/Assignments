#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int countTokens( char *str );

/* countTokens
 * input: a zero terminated string
 * output: The number of space separated tokens in str
 *
 * This method is for internal use only.  The function tokenizeString returns the count by reference.
 */
int countTokens( char *str ){
    int cnt = 0;                        /* number of tokens found */
    int strLength = strlen( str );      /* length of the string str */
    int index = 1;                      /* location in str */

    /* if str starts with a token, increment cnt */
    if( str[0]!=' ' )
        cnt++;

    /* Loop through all of the remaining chars in str */
    while( index<strLength ) {

        /* If you've found the start of a token increment cnt */
        /* (i.e., prior char = ' ' and current char is not = ' ') */
        if( str[index-1]==' ' && str[index]!=' ' ) {
            cnt++;
        }
        index++;
    }

    return cnt;
}

/* tokenizeString
 * input: a zero terminated string
 * output: an array of dynamically strings which contains the ' ' separated tokens of str, uses retTokenCount to return by reference the number of tokens in the array.
 *
 * Note: This function mallocs space.  The caller is responsible for freeing this malloc-ed array of strings.
 */
char **tokenizeString( char *str, int *retTokenCount ){

    int strLength = strlen( str );
    int cnt = countTokens( str );
    int index = 0;     /* current index into str */
    int curToken = 0;  /* current token index to be added */

    char *buffer = (char *)malloc( sizeof(char)*(strLength+1) );
    char **arrTokens = (char **)malloc( sizeof(char*)*cnt );
    if( buffer==NULL || arrTokens==NULL )
        exit(-1);

    /* Check that parameter retTokenCount is not NULL */
    if( retTokenCount != NULL )
        *retTokenCount = cnt;

    while( index<strLength ){
        int bufferIndex=0;  /* current buffer index */

        /* Skip space characters */
        while( index<strLength && str[index]==' ' )
            index++;

        /* if no new token found, leave the loop */
        if(index == strLength)
            break;

        /* Copy the next token into buffer */
        while( index<strLength && str[index]!=' ' ){
            buffer[bufferIndex] = str[index];
            index++;
            bufferIndex++;
        }
        buffer[bufferIndex] = '\0'; /* Put null terminator at end of buffer string */

        /* malloc space for most recent token */
        arrTokens[curToken] = (char *)malloc( sizeof(char)*(bufferIndex+1) );
        if( arrTokens[curToken]==NULL )
            exit(-1);

        /* copy buffer into the array of tokens */
        strcpy( arrTokens[curToken], buffer );

        curToken++;
    }
    free(buffer);

    return arrTokens;
}