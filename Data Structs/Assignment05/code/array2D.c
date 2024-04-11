#include "array2D.h"

/* mallocs and returns an array2d with the specified length and width*/
array2D* mallocArray2D( int length, int width )
{
    int i;
    array2D *arrayData = (array2D*)malloc( sizeof(array2D) );

    arrayData->length = length;
    arrayData->width = width;
    arrayData->array2D = (char**)malloc(length*sizeof(char*));

    for( i=0; i<arrayData->length; i++ )
        arrayData->array2D[i] = (char*)malloc(arrayData->width*sizeof(char));

    return arrayData;
}

void printArray2D( array2D *arrayData, bool enabled )
{
    int i, j;

    for( i=0; i<arrayData->length; i++ ){
        for( j=0; j<arrayData->width; j++ ){
            if( arrayData->array2D[i][j]=='X' )
                red( enabled );
            printf("%c", arrayData->array2D[i][j]);
            reset( enabled );
        }
        printf("\n");
    }
    printf("\n");
    reset( enabled );
}

void freeArray2D( array2D *arrayData )
{
    int i;

    for( i=0; i<arrayData->length; i++ )
        free(arrayData->array2D[i]);
    free( arrayData->array2D );
    free( arrayData );
}
