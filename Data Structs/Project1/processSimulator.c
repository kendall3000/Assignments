#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "processSimulator.h"

char* runProcessForOneTimeStep( char *pName );
bool authenticationRAM( char *pName );
bool authentication( char *pName, processData *pData  );
void startProcess( char *pName, processData *pData );

/* Cheat stuff */
static int step = 1;
static int nameNum = 0;
static processData *RAM = NULL;
static int done = 0;
static int map[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29 };

#define ZERO   0
#define ONE    1
#define TWO    2
#define THREE  3
#define FOUR   4
#define FIVE   5
#define SIX    6
#define SEVEN  7
#define EIGHT  8
#define NINE   9
#define TEN    10
#define ELEVEN 11
#define RANGE  30

/* initializeProcessData
 * input: the process name
 * output: initialized data for the process
 *
 * Initialize the data for a process.
 * Call this when a process is first added to your queue
 */
processData* initializeProcessData( char *processName ){
    /* JESS: Don't try to understand the code in this file.  It will make you sad. :( */
    processData* pData = (processData*)malloc(sizeof(processData));
    char temp[21];
    char intStr[3];
    char *priorityName;
    int i, swap;
    
     srand(time(0));
    
    while( done<1000 ){
      int a = rand()%RANGE;
      int b = rand()%RANGE;
      
      swap   = map[a];
      map[a] = map[b];
      map[b] = swap;
      done++;
    }

    if( pData==NULL ){
        fprintf(stderr, "initializeProcessData: Unable to allocate data.");
        exit(-1);
    }
    for(i=0; i<21; i++)
        pData->PN21[i] = 0;
    strncpy( pData->PN21, processName, 20 );
    
    for( i=0; i<RANGE; i++ )
        pData->heap[map[i]]=0;

    sscanf( processName, "%*[^|]|%20s", temp );
    sscanf( temp, "%3[^|]|%20s", pData->TLN, temp );
    for( i=0; i<=4; i++ ){
        sscanf( temp, "%2[^|]|%20s", intStr, temp );
        if( i==0 )
          sscanf( intStr, "%d", &pData->heap[map[ZERO]] );
        else if( i==1 )
          sscanf( intStr, "%d", &pData->heap[map[ONE]] );
        else if( i==2 )
          sscanf( intStr, "%d", &pData->heap[map[TWO]] );
        else if( i==3 )
          sscanf( intStr, "%d", &pData->heap[map[THREE]] );
        else if( i==4 )
          sscanf( intStr, "%d", &pData->heap[map[FOUR]] );
    }
    while( i<RANGE ){
        pData->heap[map[i]]=0;
        i++;
    }
    pData->heap[map[SIX]] = pData->heap[map[TWO]];
    pData->heap[map[TEN]]=25;
    pData->heap[map[SEVEN]] = processName[0]=='B';

    pData->heap[map[EIGHT]]=pData->heap[map[FOUR]];

    pData->heap[map[ONE]] = max(pData->heap[map[ONE]]/powInt(2,abs(pData->heap[map[SEVEN]]-1)),1);
    pData->heap[map[TEN]]=pData->heap[map[TEN]]<<1;
    pData->heap[map[ELEVEN]]=step;

    if( pData->heap[map[SEVEN]] ){
        priorityName = "BACKGROUND";
    }
    else{
        priorityName = "FOREGROUND";
    }

    printf( "Process data created: %s-%d (%s for %d steps)\n", pData->TLN, pData->heap[map[ZERO]], priorityName, pData->heap[map[ONE]] );

    return pData;
}

/* runProcess
 * input: the process name and a pointer to an int that contains the number of steps to run for
 * output: a bool which is true if the process finished and false if it is still incomplete
 *
 * return by reference: 
 * 1) stores at pNumSteps the number of steps run prior to the process finishing or a system call 
 * 2) stores at ppSystemCall a string which is the name of a process which is started by this one OR NULL if no process is started 
 *
 * Attempts to run the process currently loaded in RAM for k time steps.
 * If this process makes a system call the execution it will set ppSystemCall to that process's name, otherwise it sets ppSystemCall to NULL.
 * If the process completes or a system call occurs, runProcess suspends execution of this process and it writes the number of steps completed at *pNumSteps.
 */
bool runProcess( char *pName, char **ppSystemCall, int *pNumSteps ){
    int i = 0;
    *ppSystemCall = NULL;

    if( !authenticationRAM( pName ) ){
        exit(-1);
    }

    printf( "Attempting to run process: %s-%d for %d steps\n", RAM->TLN, RAM->heap[map[ZERO]], *pNumSteps );

    while( i<*pNumSteps && *ppSystemCall == NULL && RAM->heap[map[FIVE]]<RAM->heap[map[ONE]] ){
        *ppSystemCall = runProcessForOneTimeStep( pName );
        i++;
    }
    
    *pNumSteps = i;

    if( RAM->heap[map[FIVE]]>=RAM->heap[map[ONE]] && i==0 ){
        printf( "ERROR - Attempting to run process that has already completed: %s-%d\n", RAM->TLN, RAM->heap[map[ZERO]]  ); 
        exit(-1);
    }
    else if( RAM->heap[map[FIVE]]==RAM->heap[map[ONE]] ){
        printf( "Process completed after %d steps: %s-%d\n", i, RAM->TLN, RAM->heap[map[ZERO]] );
        return true;
    }
    else if( *ppSystemCall != NULL )
        printf( "Execution interrupted after %d steps: %s-%d\n", i, RAM->TLN, RAM->heap[map[ZERO]] );
    
    return false;
}

/* loadProcessData
 * input: a processData to be loaded into RAM
 * output: a string
 *
 * Prints out message saying which data was evicted and which was loaded.  If the given data is already loaded nothing is printed.
 * In the real world the RAM can contain data from multiple processes but we're keeping it simple :)
 */
void loadProcessData( processData *pData ){
    if( pData != RAM ){
        if( RAM != NULL )
            printf( "Process data evicted: %s-%d (run for %d/%d steps so far)\n", RAM->TLN, RAM->heap[map[ZERO]], RAM->heap[map[FIVE]], RAM->heap[map[ONE]] );
        RAM = pData;
        printf( "Process data loaded: %s-%d (run for %d/%d steps so far)\n", RAM->TLN, RAM->heap[map[ZERO]], RAM->heap[map[FIVE]], RAM->heap[map[ONE]] );
    }
}


/* promoteProcess
 * input: the process name and the process data
 * output: a string
 *
 * Prints out message indicating a BACKGROUND process is being promoted to FOREGROUND
 */
void promoteProcess( char *pName, processData *pData ){
    if( authentication( pName, pData ) ){
        if( pData->heap[map[SEVEN]] ) {
            pData->heap[map[SEVEN]] = 0;
            if( !(step-pData->heap[map[ELEVEN]]-pData->heap[map[TEN]]) )
                printf( "Process promoted: %s-%d (run for %d/%d steps so far)\n", pData->TLN, pData->heap[map[ZERO]], pData->heap[map[FIVE]], pData->heap[map[ONE]] );
            else if( step-pData->heap[map[ELEVEN]]-pData->heap[map[TEN]]<0 )
                printf( "ERROR - Process promoted %d step(s) too soon: %s-%d (run for %d/%d steps so far)\n", -1*(step-pData->heap[map[ELEVEN]]-pData->heap[map[TEN]]), pData->TLN, pData->heap[map[ZERO]], pData->heap[map[FIVE]], pData->heap[map[ONE]] );
            else
                printf( "ERROR - Process promoted %d step(s) too late: %s-%d (run for %d/%d steps so far)\n", step-pData->heap[map[ELEVEN]]-pData->heap[map[TEN]], pData->TLN, pData->heap[map[ZERO]], pData->heap[map[FIVE]], pData->heap[map[ONE]] );
        }
        else{
            printf( "ERROR - Attempting to promote foreground process: %s-%d (run for %d/%d steps so far)\n", pData->TLN, pData->heap[map[ZERO]], pData->heap[map[FIVE]], pData->heap[map[ONE]] );
        }

    }
}

/* freeProcessData
 * input: void
 * output: void
 *
 * Frees the processData currently loaded in RAM.  Call this after a process has run to completion.
 * Reports errors if it was run the incorrect number of steps.
 */
void freeProcessData( ){
    printf( "Process data deleted: %s-%d (run for %d/%d steps)\n", RAM->TLN, RAM->heap[map[ZERO]], RAM->heap[map[FIVE]], RAM->heap[map[ONE]] );
    if( RAM->heap[map[ONE]]>RAM->heap[map[FIVE]] ){
        printf( "ERROR - Process deleted with %d steps left to do: %s-%d\n", RAM->heap[map[ONE]]-RAM->heap[map[FIVE]], RAM->TLN, RAM->heap[map[ZERO]] );
    }
    if( RAM->heap[map[FIVE]]>RAM->heap[map[ONE]] ){
        printf( "ERROR - Process run for %d steps more than was required: %s-%d\n", RAM->heap[map[FIVE]]-RAM->heap[map[ONE]], RAM->TLN, RAM->heap[map[ZERO]]  );
    }
    if( RAM->heap[map[SEVEN]] && (step-RAM->heap[map[ELEVEN]]-RAM->heap[map[TEN]]>0) )
        printf( "ERROR - Background process was not promoted: %s-%d\n", RAM->TLN, RAM->heap[map[ZERO]] );

    free(RAM);
    RAM = NULL;
}

/************************ Code below this point is internal use only ************************/

/* runProcessForOneTimeStep
 * input: the process name and the process data
 * output: a string
 * FOR INTERNAL USE ONLY
 *
 * Simulates the given process for one time step.
 * If it makes a system call to another process it will return that process's name, otherwise it returns NULL.
 */
char* runProcessForOneTimeStep( char *pName ){
    char *ret = NULL;

    printf( "%4d - Running process: %s-%d\n", step, RAM->TLN, RAM->heap[map[ZERO]] );

    RAM->heap[map[FIVE]]++;
    //printf( "heap[map[FIVE]: %d\n", pData->heap[map[FIVE] );
    RAM->heap[map[SIX]]--;

    if( RAM->heap[map[SIX]]==0 && RAM->heap[map[THREE]]>1 ){
        ret = (char *)malloc(21);
        startProcess(ret, RAM);
        RAM->heap[map[SIX]] = RAM->heap[map[TWO]];
    }

    step++;
    return ret;
}

/* startProcess
 * FOR INTERNAL USE ONLY
 */
void startProcess( char *pName, processData *pData ){
    char temp[7][4];
    int i;

    if( pData->heap[map[THREE]]%2==1 && pData->PN21[0]=='F' )
        strcpy(temp[0],"B");
    else if( pData->heap[map[THREE]]%2==1 && pData->PN21[0]=='B' )
        strcpy(temp[0],"F");
    else{
        temp[0][0] = pData->PN21[0];
        temp[0][1] = '\0';
    }

    strcpy( temp[1], pData->TLN );

    nameNum++;
    sprintf( temp[2], "%d", (nameNum)%100 );
    sprintf( temp[3], "%d", pData->heap[map[ONE]] );

    sprintf( temp[4], "%d", pData->heap[map[TWO]] );
    sprintf( temp[5], "%d", max(pData->heap[map[THREE]]/2,1) );

    sprintf( temp[6], "%d", pData->heap[map[NINE]] );

    strcpy( pName, "" );
    for( i=0; i<6; i++ ){
        strcat( pName, temp[i] );
        strcat( pName, "|" );
    }
    strcat( pName, temp[i] );
    pData->heap[map[EIGHT]]++;
    pData->heap[map[NINE]]+=pData->heap[map[ONE]]/pData->heap[map[TWO]];
}

/* authenticationRAM
 * FOR INTERNAL USE ONLY
 */
bool authenticationRAM( char *pName ){
    if( pName==NULL ){
        fprintf(stderr, "ERROR - Authentication failed - pName is NULL.\n");
        return false;
    }
    else if( RAM == NULL ){
        fprintf(stderr, "ERROR - Authentication failed - data was not loaded into RAM (be sure to call loadProcessData).\n");
        return false;
    }
    else if( RAM->PN21==NULL ){
        fprintf(stderr, "ERROR - Authentication failed - data in RAM may have been corrupted.\n");
        return false;
    }
    else if( strcmp(pName, RAM->PN21) ){
        fprintf(stderr, "ERROR - Authentication failed - incorrect data was loaded into RAM (be sure to call loadProcessData).\n");
        return false;
    }
    return true;
}

/* authentication
 * FOR INTERNAL USE ONLY
 */
bool authentication( char *pName, processData *pData  ){
    if( pName==NULL ){
        fprintf(stderr, "ERROR - Authentication failed - pName is NULL.\n");
        return false;
    }
    else if( pData == NULL ){
        fprintf(stderr, "ERROR - Authentication failed - pData is NULL.\n");
        return false;
    }
    else if( pData->PN21==NULL ){
        fprintf(stderr, "ERROR - Authentication failed - data in pData may have been corrupted.\n");
        return false;
    }
    else if( strcmp(pName, pData->PN21) ){
        fprintf(stderr, "ERROR - Authentication failed - mismatch of data associated with pName and pData.\n");
        return false;
    }
    return true;
}

/* max
 * FOR INTERNAL USE ONLY
 */
int max( int a, int b ){
    if(a>b)
        return a;
    else
        return b;
}

/* powInt
 * FOR INTERNAL USE ONLY
 */
int powInt( int a, int b ){
    int product = 1;
    while( b>0 ){
        product*=a;
        b--;
    }
    return product;
}
