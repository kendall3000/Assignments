#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "queue.h"
#include "multilevelQueueScheduler.h"
#include "processSimulator.h"

void testData( char *testData[], int testDataSize, int testNumber );

priority getPriority(char* processName);

int main( int argc, char *argv[] )
{
    char *testData1[] = {"F|NEW|00|12|10|04|00",
                        "B|LNG|00|10|07|03|00",
                        "F|SMP|00|30|08|31|00",
                        "F|RPD|00|09|03|32|00",
                        "F|VID|00|40|99|01|00"};

    int testData1Size = 5;
    
    printNames( );

    testData( testData1, testData1Size, 1 );

    return 0;
}

void testData( char *testData[], int testDataSize, int testNumber )
{
    schedule *ps = createSchedule();
    char *name;
    int i = 0;
    
    printf( "\n\n------------ START OF TEST #%d ------------\n\n", testNumber );

    //Call addNewProcessToSchedule for all of the starting processes
    for( i=0; i<testDataSize; i++){
        char *temp = (char *)malloc(strlen(testData[i])+1);
        strcpy( temp, testData[i] );
        addNewProcessToSchedule( ps, temp, getPriority(temp) );
    }
    printf( "\n" );

    //Simulate time steps until the schedule is finished (i.e. all work finished for all processes)
    while( isScheduleUnfinished( ps ) ){
        name = runNextProcessInSchedule( ps );
        if( name!= NULL )
            addNewProcessToSchedule( ps, name, getPriority(name) );
        printf( "\n" );
    }
    freeSchedule( ps );
    
    printf( "------------ END OF TEST #%d ------------\n", testNumber );
}

priority getPriority(char* processName){
    char priorityString[2];
    priority p;
    //Read runtime from the 1st |-separated value in the string
    sscanf(processName, "%1[^|]", priorityString);
    if( !strcmp(priorityString, "F") )
        p = FOREGROUND;
    else if( !strcmp(priorityString, "B") )
        p = BACKGROUND;
    else{
        fprintf(stderr, "invalid priority\n");
        exit(-1);
    }

    return p;
}