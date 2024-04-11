#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "stack.h"
#include "booleanEvaluation.h"

#define BUFFER_SIZE 200
#define NUM_EVAL_FILES 1
#define NUM_PTI_FILES 1
#define PRINT_CORRECT TRUE
const char * EVAL_FILE_NAMES[] = { "evaluatePostfixTestData.txt" };
const char * PTI_FILE_NAMES[] = { "postfixToInfixTestData.txt" };

void testFile( const char dataFile[], char *(*f)( char *));
void trimSpaceChars( char *buffer );

int main( int argc, char *argv[] )
{
    int i;
    printf("\n");
    printNames( );

    /* Test evaluatePostfix implementation */
    for( i=0; i<NUM_EVAL_FILES ; i++ ){
        printf("\n");
        printf("Test file = %s: \n", EVAL_FILE_NAMES[i]);
        printf("--------------------------------------\n\n");
        testFile( EVAL_FILE_NAMES[i], evaluatePostfix );
    }

    /* Test postfixToInfix implementation */
    for( i=0; i<NUM_PTI_FILES ; i++ ){
        printf("\n");
        printf("Test file = %s: \n", PTI_FILE_NAMES[i]);
        printf("--------------------------------------\n\n");
        testFile( PTI_FILE_NAMES[i], postfixToInfix );
    }

    return 0;
}

/* testFile
 * input: name of input file, function to test
 * output: none
 *
 * Runs the specified function on inputs from the given file.
 * Prints whether the given function returns the correct value
 * This is the only function that prints in your program.
 */
void testFile( const char dataFile[], char *(*f)( char *))
{
    char *strcopy;

    char inputBuffer[BUFFER_SIZE] = "";
    char solutionBuffer[BUFFER_SIZE] = "";
    char *result;
    boolean correct = TRUE;


    /* Try to open the data file */
    FILE *data = fopen( dataFile, "r" );
    if( data==NULL )
    {
        printf("Failed to open input file %s\n", dataFile);
        exit(-1);
    }

    while( TRUE )
    {
        /* Read line of operations */
        if( fgets( inputBuffer, BUFFER_SIZE, data )==NULL )
        {
            break;
        }
        trimSpaceChars( inputBuffer );

        /* Read solution line */
        if( fgets( solutionBuffer, BUFFER_SIZE, data )==NULL )
        {
            printf("File formatting incorrect\n");
            break;
        }
        trimSpaceChars( solutionBuffer );

        strcopy = (char *)malloc( strlen(inputBuffer)+1 );
        strcpy( strcopy, inputBuffer );

        /* process the boolean string using the student's code */
        result = f( strcopy );

        /* check if result = provided solution */
        if( strcmp(solutionBuffer, result)==0 && PRINT_CORRECT )
        {
            /* Set PRINT_CORRECT to FALSE to skip printing the correct test cases */
            printf("\"%s\" = %s\nYour solution is correct\n\n", inputBuffer, solutionBuffer);
        }
        else if( strcmp(solutionBuffer, result)!=0 )
        {
            correct = FALSE;
            printf("\"%s\"\nYour solution is incorrect\n", inputBuffer);
            printf("Expected %s but your function returned %s\n\n", solutionBuffer, result);
        }

        free( result );
        free( strcopy );
    }
    if( correct==TRUE )
    {
         printf("All test cases were correct\n\n");
    }
    fclose( data );
}

/* trimSpaceChars
 * input: a string
 * output: none
 *
 * Removes leading and trailing white space characters for the string
 */
void trimSpaceChars( char *buffer )
{
    int i=0;
    int j=0;
    /* skip leading white space */
    while( isspace(buffer[i]) )
        i++;
    while( i<BUFFER_SIZE )
    {
        /* Replace the newline with a null char */
        if( buffer[i]=='\n' )
        {
            buffer[j]='\0';
            break;
        }
        buffer[j] = buffer[i];
        i++;
        j++;
    }
    j--;
    /* truncate trailing white space */
    while( isspace(buffer[j]) )
        j--;
    buffer[j+1]='\0';
}