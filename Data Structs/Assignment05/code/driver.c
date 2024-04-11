#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#include "graphPathAlg.h"
#include "graph.h"
#include "point2D.h"
#include "queuePoint2D.h"
#include "array2D.h"

/* Largest size of maze to be printed */
#define MAX_MAZE_PRINT 45

/* Print color coding for output (may not work outside of Linux environment) */
#define MAZE_PRINT_COLOR false

/* parameters to determine how to test student hasPath function */
#define TEST_HASPATH true
#define HASPATH_MIN_SIZE 16 /* Do not lower this below 15 */
#define HASPATH_MAX_SIZE 44
#define HASPATH_UPDATE_SIZE 4

/* parameters to determine how to test student findNearest function */
#define TEST_FINDNEAREST true
#define FINDNEAREST_MIN_SIZE 16 /* Do not lower this below 15 */
#define FINDNEAREST_MAX_SIZE 44
#define FINDNEAREST_UPDATE_SIZE 4

/* parameters to determine how to test student findTunnelRoute function */
#define TEST_FINDTUNNELROUTE true
#define FINDTUNNELROUTE_MIN_SIZE 16 /* Do not lower this below 15 */
#define FINDTUNNELROUTE_MAX_SIZE 40
#define FINDTUNNELROUTE_UPDATE_SIZE 8

/* These allow suppression of maze printing depending on whether the test succeeds */
#define PRINT_MAZE_ON_SUCCESS false
#define PRINT_MAZE_ON_UNKNOWN false
#define PRINT_MAZE_ON_FAILURE true

/* Suppress output of true positive/true negative/false positive/false negative and success counts */
#define SUPPRESS_OUTPUT_ON_SUCCESS false

/************************ TESTING FUNCTIONS ************************/
void testHasPath( int minSize, int maxSize, int update );
void testFindNearestFinish( int minSize, int maxSize, int update );
void testFindTunnelRoute( int minSize, int maxSize, int update );

/************************ REPORTING/PRINTING FUNCTIONS ************************/
void recordSolution( array2D *maze, char *name, pathResult correctResult, pathResult testResult,
                    int *truePositive, int *trueNegative, int *falsePositive, int *falseNegative, bool* implemented, bool passesOtherConds, char *failureMsg );
void printResults( char* name, int truePositive, int trueNegative, int falsePositive, int falseNegative, bool implemented, bool passesOtherConds );

/************************ MAZE CREATION FUNCTIONS ************************/
array2D* createBasicMaze( int size, bool path, Point2D* start );
array2D* createMultipleFinishMaze( int size, int *shortestPathLength );
array2D* createSimplePathMaze( int size, int *longestPathLength, pathResult *presult );
array2D* createTunnelMaze( int size, bool path, int k );
array2D* createAdvancedTunnelMaze( int size, bool path );

void addDeadEnds( array2D *maze );
void fillMazeWithSymbol( array2D *maze, Point2D startPoint, Point2D endPoint, char c );
void replaceSymbolInMaze( array2D *maze, Point2D startPoint, Point2D endPoint, char c, char d );
void createMazeBorder( array2D *maze, int start, int end );
void createPath( array2D *maze, int start, int end, bool path );
int createPathBetweenPoints( array2D *maze, Point2D startP, Point2D endP, Point2D tlCorner, Point2D brCorner, int probability, char c );
int createSimplePathBetweenPoints( array2D *maze, Point2D startP, Point2D endP, Point2D tlCorner, Point2D brCorner, int probability, char c, pathResult *presult );

int replaceZero( int dir );
bool adjacent( Point2D p1, Point2D p2 );
int median( int a, int b, int c );
int min( int a, int b );
int max( int a, int b );


int main( int argc, char *argv[] )
{
    clock_t start, end;
    srand(time(0));

    printName( );
    printf("\n");

    /* Test basic path finding capability */
    if( TEST_HASPATH ){
        start = clock();
        testHasPath( HASPATH_MIN_SIZE, HASPATH_MAX_SIZE, HASPATH_UPDATE_SIZE );
        end = clock();
        printf( "hasPath testing took %lf seconds\n\n", (double)(end - start)/ CLOCKS_PER_SEC );
    }

    /* Test function for finding nearest finish to graph */
    if( TEST_FINDNEAREST ){
        start = clock();
        testFindNearestFinish( FINDNEAREST_MIN_SIZE, FINDNEAREST_MAX_SIZE, FINDNEAREST_UPDATE_SIZE );
        end = clock();
        printf( "findNearestFinish testing took %lf seconds\n\n", (double)(end - start)/ CLOCKS_PER_SEC );
    }

    /* Test function for finding tunnel route */
    if( TEST_FINDTUNNELROUTE ){
        start = clock();
        testFindTunnelRoute( FINDTUNNELROUTE_MIN_SIZE, FINDTUNNELROUTE_MAX_SIZE, FINDTUNNELROUTE_UPDATE_SIZE );
        end = clock();
        printf( "findTunnelRoute testing took %lf seconds\n\n", (double)(end - start)/ CLOCKS_PER_SEC );
    }

    return 0;
}

/************************ TESTING FUNCTIONS ************************/

/* Test hasPath */
void testHasPath( int minSize, int maxSize, int update )
{
    int size, falsePositive=0, falseNegative=0, truePositive=0, trueNegative=0;
    bool implemented = true;
    array2D *maze;

    /* Test basic path finding capability */
    for( size=minSize; size<=maxSize; size+=update )
    {
        maze = createBasicMaze( size, PATH_FOUND, NULL );
        recordSolution( maze, "hasPath", PATH_FOUND, hasPath( maze ), &truePositive, &trueNegative, &falsePositive, &falseNegative, &implemented, true, NULL );
        freeArray2D( maze );
    }
    for( size=minSize; size<=maxSize; size+=update )
    {
        maze = createBasicMaze( size, PATH_IMPOSSIBLE, NULL );
        recordSolution( maze, "hasPath", PATH_IMPOSSIBLE, hasPath( maze ), &truePositive, &trueNegative, &falsePositive, &falseNegative, &implemented, true, NULL );
        freeArray2D( maze );
    }
    printResults( "hasPath", truePositive, trueNegative, falsePositive, falseNegative, implemented, true );
    if( falsePositive==0 && falseNegative==0 && implemented )
            printf( "All test cases succeeded.  Good job!\n" );
}

/* Test findNearestFinish */
void testFindNearestFinish( int minSize, int maxSize, int update )
{
    int size, falsePositive=0, falseNegative=0, truePositive=0, trueNegative=0;
    int correctSPLength, testSPLength, numSPsCorrect=0, numSPsIncorrect=0;
    pathResult testResult;
    bool implemented = true;
    array2D *maze;
    char failureMsg[100];

    for( size=minSize; size<=maxSize; size+=update )
    {
        maze = createMultipleFinishMaze( size, &correctSPLength );
        testResult = findNearestFinish( maze, &testSPLength );

        if( correctSPLength==testSPLength )
            numSPsCorrect++;
        else if( (PRINT_MAZE_ON_FAILURE && implemented) || (PRINT_MAZE_ON_UNKNOWN && !implemented) ){
            sprintf( failureMsg, "FAILURE - findNearestFinish - Shortest path has length = %d but your function returned %d\n", correctSPLength, testSPLength);
            numSPsIncorrect++;
        }
        else
            numSPsIncorrect++;

        recordSolution( maze, "findNearestFinish", PATH_FOUND, testResult, &truePositive, &trueNegative, &falsePositive, &falseNegative, &implemented, correctSPLength==testSPLength, failureMsg );
        freeArray2D( maze );
    }
    for( size=minSize; size<=maxSize; size+=update )
    {
        maze = createBasicMaze( size, PATH_IMPOSSIBLE, NULL );
        recordSolution( maze, "findNearestFinish", PATH_IMPOSSIBLE, findNearestFinish( maze, &testSPLength ), &truePositive, &trueNegative, &falsePositive, &falseNegative, &implemented, true, NULL );
        freeArray2D( maze );
    }

    printResults( "findNearestFinish", truePositive, trueNegative, falsePositive, falseNegative, implemented, (numSPsIncorrect==0) );
    if( implemented && ( !SUPPRESS_OUTPUT_ON_SUCCESS || numSPsIncorrect!=0 ) )
        printf( "Correctly identified the shortest path length in %d out of %d test cases\n", numSPsCorrect, numSPsIncorrect+numSPsCorrect );
    if( falsePositive==0 && falseNegative==0 && (numSPsIncorrect==0) && implemented )
        printf( "All test cases succeeded.  Good job!\n" );
}

/* Test findTunnelRoute */
void testFindTunnelRoute( int minSize, int maxSize, int update )
{
    int size, tunnel, falsePositive=0, falseNegative=0, truePositive=0, trueNegative=0;
    bool implemented = true;
    array2D *maze;
    pathResult testResult;

    /* Test tunnel route finding capability */
    for( size=minSize; size<=maxSize; size+=update )
    {
        tunnel = (size-6)/2;
        maze = createTunnelMaze( size, PATH_FOUND, tunnel );
        testResult = findTunnelRoute( maze, tunnel );

        if( (PRINT_MAZE_ON_SUCCESS && PATH_FOUND==testResult) || (PRINT_MAZE_ON_FAILURE && PATH_IMPOSSIBLE==testResult) || (PRINT_MAZE_ON_UNKNOWN && PATH_UNKNOWN==testResult) )
            printf( "TESTING WITH TUNNEL LENGTH = %d\n", tunnel );

        recordSolution( maze, "findTunnelRoute", PATH_FOUND, testResult, &truePositive, &trueNegative, &falsePositive, &falseNegative, &implemented, true, NULL );
        freeArray2D( maze );
    }
    /* Test advanced tunnel route finding capability */
    for( size=minSize; size<=maxSize; size+=update )
    {
        tunnel = 2*size-8;
        maze = createAdvancedTunnelMaze( size, PATH_FOUND );
        testResult = findTunnelRoute( maze, tunnel );

        if( (PRINT_MAZE_ON_SUCCESS && PATH_FOUND==testResult) || (PRINT_MAZE_ON_FAILURE && PATH_IMPOSSIBLE==testResult) || (PRINT_MAZE_ON_UNKNOWN && PATH_UNKNOWN==testResult) )
            printf( "TESTING WITH TUNNEL LENGTH = %d\n", tunnel );

        recordSolution( maze, "findTunnelRoute", PATH_FOUND, testResult, &truePositive, &trueNegative, &falsePositive, &falseNegative, &implemented, true, NULL );
        freeArray2D( maze );
    }
    for( size=minSize; size<=maxSize; size+=update )
    {
        tunnel = (size-6)/2;
        maze = createTunnelMaze( size, PATH_FOUND, tunnel );
        testResult = findTunnelRoute( maze, tunnel-1 );

        if( (PRINT_MAZE_ON_SUCCESS && PATH_IMPOSSIBLE==testResult) || (PRINT_MAZE_ON_FAILURE && PATH_FOUND==testResult) || (PRINT_MAZE_ON_UNKNOWN && PATH_UNKNOWN==testResult) )
            printf( "TESTING WITH TUNNEL LENGTH = %d\n", tunnel-1 );

        recordSolution( maze, "findTunnelRoute", PATH_IMPOSSIBLE, testResult, &truePositive, &trueNegative, &falsePositive, &falseNegative, &implemented, true, NULL );
        freeArray2D( maze );
    }
    /* Test advanced tunnel route finding capability */
    for( size=minSize; size<=maxSize; size+=update )
    {
        tunnel = 2*size-8;
        maze = createAdvancedTunnelMaze( size, PATH_FOUND );
        testResult = findTunnelRoute( maze, tunnel-1 );

        if( (PRINT_MAZE_ON_SUCCESS && PATH_IMPOSSIBLE==testResult) || (PRINT_MAZE_ON_FAILURE && PATH_FOUND==testResult) || (PRINT_MAZE_ON_UNKNOWN && PATH_UNKNOWN==testResult) )
            printf( "TESTING WITH TUNNEL LENGTH = %d\n", tunnel-1 );

        recordSolution( maze, "findTunnelRoute", PATH_IMPOSSIBLE, testResult, &truePositive, &trueNegative, &falsePositive, &falseNegative, &implemented, true, NULL );
        freeArray2D( maze );
    }
    printResults( "findTunnelRoute", truePositive, trueNegative, falsePositive, falseNegative, implemented, true );
    if( falsePositive==0 && falseNegative==0 && implemented )
            printf( "All test cases succeeded.  Good job!\n" );
}

/************************ REPORTING/PRINTING FUNCTIONS ************************/

/* Determines the type of error that occurred and updates parameters accordingly */
void recordSolution( array2D* maze, char *name, pathResult correctResult, pathResult testResult,
                     int *truePositive, int *trueNegative, int *falsePositive, int *falseNegative, bool* implemented, bool passesOtherConds, char *failureMsg )
{
    int size = maze->length;
    if( testResult!=PATH_FOUND && testResult!=PATH_IMPOSSIBLE && testResult!=PATH_UNKNOWN ){
        printf("ERROR - %s - You should only return PATH_FOUND, PATH_IMPOSSIBLE, or PATH_UNKNOWN \n", name );
        if( PRINT_MAZE_ON_UNKNOWN ){
            if( !passesOtherConds ){red( MAZE_PRINT_COLOR ); printf("%s", failureMsg); reset( MAZE_PRINT_COLOR );}
            if( size<=MAX_MAZE_PRINT ) printArray2D( maze, MAZE_PRINT_COLOR  );
            else printf("Maze too large to display\n\n");
        }
        (*implemented) = false;    
    }
    else if( correctResult==PATH_FOUND && testResult==PATH_FOUND ){
        if( PRINT_MAZE_ON_SUCCESS || (!passesOtherConds&&PRINT_MAZE_ON_FAILURE&&*implemented) ){
            green( MAZE_PRINT_COLOR );
            printf("SUCCESS - %s - Path found for maze of size %d (true positive)\n", name, size);
            reset( MAZE_PRINT_COLOR );
            if( !passesOtherConds ){red( MAZE_PRINT_COLOR ); printf("%s", failureMsg); reset( MAZE_PRINT_COLOR );}
            if( size<=MAX_MAZE_PRINT ) printArray2D( maze, MAZE_PRINT_COLOR  );
            else printf("Maze too large to display\n\n");
        }
        (*truePositive)++;
    }
    else if( correctResult==PATH_FOUND && testResult==PATH_IMPOSSIBLE ){
        if( PRINT_MAZE_ON_FAILURE ){
            red( MAZE_PRINT_COLOR );
            printf("FAILURE - %s - Path not found for maze of size %d (false negative)\n", name, size);
            reset( MAZE_PRINT_COLOR );
            if( !passesOtherConds ){red( MAZE_PRINT_COLOR ); printf("%s", failureMsg); reset( MAZE_PRINT_COLOR );}
            if( size<=MAX_MAZE_PRINT ) printArray2D( maze, MAZE_PRINT_COLOR  );
            else printf("Maze too large to display\n\n");
        }
        (*falseNegative)++;
    }
    else if( correctResult==PATH_IMPOSSIBLE && testResult==PATH_IMPOSSIBLE ){
        if( PRINT_MAZE_ON_SUCCESS || (!passesOtherConds&&PRINT_MAZE_ON_FAILURE&&*implemented) ){
            green( MAZE_PRINT_COLOR );
            printf("SUCCESS - %s - Path not found for maze of size %d (true negative)\n", name, size);
            reset( MAZE_PRINT_COLOR );
            if( !passesOtherConds ){red( MAZE_PRINT_COLOR ); printf("%s", failureMsg); reset( MAZE_PRINT_COLOR );}
            if( size<=MAX_MAZE_PRINT ) printArray2D( maze, MAZE_PRINT_COLOR  );
            else printf("Maze too large to display\n\n");
        }
        (*trueNegative)++;
    }
    else if( correctResult==PATH_IMPOSSIBLE && testResult==PATH_FOUND ){
        if( PRINT_MAZE_ON_FAILURE ){
            red( MAZE_PRINT_COLOR );
            printf("FAILURE - %s - Path found for maze of size %d (false positive)\n", name, size);
            reset( MAZE_PRINT_COLOR );
            if( !passesOtherConds ){red( MAZE_PRINT_COLOR ); printf("%s", failureMsg); reset( MAZE_PRINT_COLOR );}
            if( size<=MAX_MAZE_PRINT ) printArray2D( maze, MAZE_PRINT_COLOR  );
            else printf("Maze too large to display\n\n");
        }
        (*falsePositive)++;
    }
    else if( testResult==PATH_UNKNOWN ){
        if( PRINT_MAZE_ON_UNKNOWN ){
            if( !passesOtherConds ){red( MAZE_PRINT_COLOR ); printf("%s", failureMsg); reset( MAZE_PRINT_COLOR );}
            if( size<=MAX_MAZE_PRINT ) printArray2D( maze, MAZE_PRINT_COLOR  );
            else printf("Maze too large to display\n\n");
        }
        (*implemented) = false;
    }
}

void printResults( char* name, int truePositive, int trueNegative, int falsePositive, int falseNegative, bool implemented, bool passesOtherConds ){
    printf( "%s Summary of Results:\n", name );
    printf( "------------------------------------------------\n" );
    if( implemented && ( !SUPPRESS_OUTPUT_ON_SUCCESS || falsePositive+falseNegative!=0 ) ){
        green( MAZE_PRINT_COLOR );
        printf( "True Positives:  %5d, True Negatives:  %5d\n", truePositive, trueNegative );
        red( MAZE_PRINT_COLOR );
        printf( "False Positives: %5d, False Negatives: %5d\n", falsePositive, falseNegative );
        reset( MAZE_PRINT_COLOR );
    }
    else if( !implemented && !PRINT_MAZE_ON_UNKNOWN ){
        yellow( MAZE_PRINT_COLOR );
        printf("NOT IMPLEMENTED - %s - This function is not yet implemented\n", name);
        reset( MAZE_PRINT_COLOR );
    }
}

/************************ MAZE CREATION/PRINTING FUNCTIONS ************************/

//Create and fill in a randomly generated maze with length and width = size
array2D* createBasicMaze( int size, bool path, Point2D *start )
{
    int i, dist, numRandPoints;
    Point2D startPoint, endPoint, tlCorner, brCorner, randomPoint, prevPoint;

    startPoint = createPoint(2,rand()%(size-4) + 2);
    endPoint = createPoint(size-3,rand()%(size-4) + 2);

    tlCorner = createPoint(1,1);
    brCorner = createPoint(size-2,size-2);

    numRandPoints = (rand()%size)/2;

    array2D* maze = mallocArray2D( size, size );
    fillMazeWithSymbol( maze, createPoint(0, 0), createPoint(size-1, size-1), 'X' );
    fillMazeWithSymbol( maze, createPoint(startPoint.x-2, startPoint.y-2), createPoint(startPoint.x+2, startPoint.y+2), ' ' );
    fillMazeWithSymbol( maze, createPoint(endPoint.x-2, endPoint.y-2), createPoint(endPoint.x+2, endPoint.y+2), ' ' );

    /* create a trail of random points to connect startPoint to endPoint */
    prevPoint = startPoint;
    for(i=0; i<numRandPoints; i++){
        randomPoint = createPoint(rand()%(size-4) + 2,rand()%(size-4) + 2);

        createPathBetweenPoints( maze, prevPoint, randomPoint, tlCorner, brCorner, 70, ' ' );
        prevPoint = randomPoint;
    }
    createPathBetweenPoints( maze, prevPoint, endPoint, tlCorner, brCorner, 70, ' ' );

    dist = abs(startPoint.x - endPoint.x)-2;
    dist = rand()%dist+1;
    if(!path)
        createPathBetweenPoints( maze, createPoint(startPoint.x+dist, tlCorner.y), createPoint(endPoint.x-dist, brCorner.y),
                                createPoint(startPoint.x+1, tlCorner.y), createPoint(endPoint.x-1, brCorner.y), 100, 'X' );

    createMazeBorder( maze, 0, size-1 );

    maze->array2D[startPoint.x][startPoint.y] = 'S';
    maze->array2D[endPoint.x][endPoint.y] = 'F';
    if( start != NULL )
        *start = startPoint;

    return maze;
}

//Create and fill in a randomly generated maze with length and width = size
array2D* createMultipleFinishMaze( int size, int *shortestPathLength )
{
    int i, curDist, numRandPoints;
    Point2D startPoint, endPoint, endPointDownUp, tlCorner, brCorner, randomPoint;
    Queue* q = createQueue();

    startPoint = createPoint(size/2+1,size-4);
    endPointDownUp = createPoint(size/2+1,size-2);

    tlCorner = createPoint(1,1);
    brCorner = createPoint(size-2,size-2);

    numRandPoints = (rand()%size)/4;

    array2D* maze = mallocArray2D( size, size );
    fillMazeWithSymbol( maze, createPoint(0, 0), createPoint(size-1, size-1), 'X' );

    /* create a trail of points to connect startPoint to endPointDownUp */
    curDist = 0;
    curDist += createPathBetweenPoints( maze, startPoint, createPoint( brCorner.x, startPoint.y ), tlCorner, brCorner, 100, ' ' );
    curDist += createPathBetweenPoints( maze, createPoint( brCorner.x, startPoint.y ), createPoint( brCorner.x, endPointDownUp.y ), tlCorner, brCorner, 100, ' ' );
    curDist += createPathBetweenPoints( maze, createPoint( brCorner.x, endPointDownUp.y ), endPointDownUp, tlCorner, brCorner, 100, ' ' );
    *shortestPathLength = curDist;
    enqueue( q, endPointDownUp );

    for( i=0; i<numRandPoints; i++){
        randomPoint = createPoint( rand()%(size-2)+1, rand()%(size/2)+1 );
        if( !equals(startPoint,randomPoint) ){ /* don't overwrite start point */
            enqueue( q, randomPoint );
            curDist = createPathBetweenPoints( maze, startPoint, randomPoint, tlCorner, brCorner, 100, ' ' );
            if( curDist<*shortestPathLength )
                *shortestPathLength = curDist;
        }
    }

    createMazeBorder( maze, 0, size-1 );

    maze->array2D[startPoint.x][startPoint.y] = 'S';
    while( !isEmptyQueue(q) ){
        endPoint = dequeue( q );
        maze->array2D[endPoint.x][endPoint.y] = 'F';
    }
    freeQueue(q);

    return maze;
}

//Create and fill in a randomly generated maze with length and width = size that requires a tunnel of length k
array2D* createTunnelMaze( int size, bool path, int k ){
    array2D* maze = createBasicMaze( size, PATH_FOUND, NULL );
    Point2D startPoint, endPoint;

    startPoint = createPoint( 4+rand()%(size-(k+8)), 1 );
    endPoint = createPoint( startPoint.x+k+1, size-2 );

    fillMazeWithSymbol( maze, startPoint, endPoint, 'X' );
    fillMazeWithSymbol( maze, startPoint, createPoint( startPoint.x, endPoint.y ), ' ' );
    fillMazeWithSymbol( maze, createPoint( endPoint.x, startPoint.y ), endPoint, ' ' );

    return maze;
}

//Create and fill in a randomly generated maze with length and width = size that requires a tunnel of length 2*(size-1)-1
array2D* createAdvancedTunnelMaze( int size, bool path ){
    array2D* maze = mallocArray2D( size, size );
    fillMazeWithSymbol( maze, createPoint(0, 0), createPoint(size-1, size-1), 'X' );
    
    maze->array2D[1][1] = 'S';
    maze->array2D[size-2][size-2] = 'F';
    
    maze->array2D[rand()%(size-4)+2][rand()%(size-4)+2] = ' ';

    return maze;
}

//Create and fill in a randomly generated maze with length and width = size
array2D* createSimplePathMaze( int size, int *longestPathLength, pathResult *presult )
{
    Point2D startPoint, endPoint, tlCorner, brCorner;

    startPoint = createPoint(1,1);
    endPoint = createPoint(size-2,size-2);

    tlCorner = createPoint(1,1);
    brCorner = createPoint(size-2,size-2);

    array2D* maze = mallocArray2D( size, size );
    fillMazeWithSymbol( maze, createPoint(0, 0), createPoint(size-1, size-1), 'X' );

    /* create a simple path to connect startPoint to endPoint */
    *longestPathLength = createSimplePathBetweenPoints( maze, startPoint, endPoint, tlCorner, brCorner, 70, ' ', presult );

    createMazeBorder( maze, 0, size-1 );

    maze->array2D[startPoint.x][startPoint.y] = 'S';
    maze->array2D[endPoint.x][endPoint.y] = 'F';

    return maze;
}

void addDeadEnds( array2D* maze ){
    int i, j, count = 0;
    bool changed = true;

    char** m = maze->array2D;

    while( changed == true && count<10 ){
        changed = false;
        //count++;
        for( i=1; i<maze->length-1; i++ )
            for( j=1; j<maze->width-1; j++ )
                if( m[i][j]=='X' ) //&& ((m[i-1][j-1]=='X') + (m[i-1][j+1]=='X') + (m[i+1][j-1]=='X') + (m[i+1][j+1]=='X'))<4)
                    if( (m[i-1][j]=='X' && m[i+1][j]=='X' && m[i][j-1]=='X' && m[i][j+1]!='X' && m[i-1][j-1]=='X' && m[i+1][j-1]=='X') ||
                        (m[i-1][j]=='X' && m[i+1][j]=='X' && m[i][j+1]=='X' && m[i][j-1]!='X' && m[i-1][j+1]=='X' && m[i+1][j+1]=='X') ||
                        (m[i-1][j]=='X' && m[i][j-1]=='X' && m[i][j+1]=='X' && m[i+1][j]!='X' && m[i-1][j-1]=='X' && m[i-1][j+1]=='X') ||
                        (m[i+1][j]=='X' && m[i][j-1]=='X' && m[i][j+1]=='X' && m[i-1][j]!='X' && m[i+1][j-1]=='X' && m[i+1][j+1]=='X') )
                    {
                        m[i][j] = ' ';
                        changed = true;
                    }
    }
}

//Fill from the startPoint to the endPoint of the maze with symbol c
void fillMazeWithSymbol( array2D* maze, Point2D startPoint, Point2D endPoint, char c )
{
    int i, j;
    int xdir = (startPoint.x <= endPoint.x) ? 1: -1;
    int ydir = (startPoint.y <= endPoint.y) ? 1: -1;

    for( i=startPoint.x; i<=endPoint.x; i+=xdir )
        for( j=startPoint.y; j<=endPoint.y; j+=ydir )
            maze->array2D[i][j] = c;
}

//Replace symbol c with symbol d from startPoint to the endPoint of the maze
void replaceSymbolInMaze( array2D* maze, Point2D startPoint, Point2D endPoint, char c, char d )
{
    int i, j;
    int xdir = (startPoint.x <= endPoint.x) ? 1: -1;
    int ydir = (startPoint.y <= endPoint.y) ? 1: -1;

    for( i=startPoint.x; i<=endPoint.x; i+=xdir )
        for( j=startPoint.y; j<=endPoint.y; j+=ydir )
            if( maze->array2D[i][j] == c )
              maze->array2D[i][j] = d;

}

//Create a border of 'X' around the maze
void createMazeBorder( array2D* maze, int start, int end )
{
    int i,j;

    for( i=start; i<=end; i++)
        for( j=start; j<=end; j++)
            if( i==start || i==end || j==start || j==end)
                maze->array2D[i][j] = 'X';
}

int createPathBetweenPoints( array2D* maze, Point2D startP, Point2D endP, Point2D tlCorner, Point2D brCorner, int probability, char c )
{
    int xdir, ydir;
    int numSteps = 0;
    Point2D curP = startP;

    if( median( tlCorner.x, startP.x, brCorner.x )!=startP.x || median( tlCorner.y, startP.y, brCorner.y )!=startP.y ||
        median( tlCorner.x, endP.x, brCorner.x )!=endP.x || median( tlCorner.y, endP.y, brCorner.y )!=endP.y ){
        printf("ERROR - createPathBetweenPoints - createPathBetweenPoints unable to link startP to endP\n");
        exit(-1);
    }


    while( !equals( curP, endP ) )
    {

        xdir = (endP.x-curP.x)!=0 ? (endP.x-curP.x)/abs(endP.x-curP.x) : 0;
        ydir = (endP.y-curP.y)!=0 ? (endP.y-curP.y)/abs(endP.y-curP.y) : 0;

        if( rand()%100>=probability )
            xdir = replaceZero(xdir) ;
        if( rand()%100>=probability )
            ydir = replaceZero(ydir) ;

        if( xdir!=0 && median( tlCorner.x, curP.x+xdir, brCorner.x ) == curP.x+xdir ){
            curP.x += xdir;
            numSteps++;
        }

        maze->array2D[curP.x][curP.y] = c;

        if( ydir!=0 && median( tlCorner.y, curP.y+ydir, brCorner.y ) == curP.y+ydir ){
            curP.y += ydir;
            numSteps++;
        }

        maze->array2D[curP.x][curP.y] = c;
    }
    return numSteps;
}

int createSimplePathBetweenPoints( array2D* maze, Point2D startP, Point2D endP, Point2D tlCorner, Point2D brCorner, int probability, char c, pathResult *presult )
{
    int xdir, ydir;
    int numSteps = 0;
    Point2D curP = startP;

    if( median( tlCorner.x, startP.x, brCorner.x )!=startP.x || median( tlCorner.y, startP.y, brCorner.y )!=startP.y ||
        median( tlCorner.x, endP.x, brCorner.x )!=endP.x || median( tlCorner.y, endP.y, brCorner.y )!=endP.y ){
        printf("ERROR - createSimplePathBetweenPoints - createPathBetweenPoints unable to link startP to endP\n");
        exit(-1);
    }

    maze->array2D[startP.x][startP.y] = ' ';

    while( abs(curP.x-endP.x)+abs(curP.y-endP.y)>1 )
    {
        if( (maze->array2D[curP.x-1][curP.y] == c || curP.x-1<tlCorner.x) && (maze->array2D[curP.x+1][curP.y] == c || curP.x+1>brCorner.x) &&
            (maze->array2D[curP.x][curP.y-1] == c|| curP.y-1<tlCorner.y) && (maze->array2D[curP.x][curP.y+1] == c || curP.y+1>brCorner.y) )
            {
                *presult = PATH_IMPOSSIBLE;
                return -1;
            }

        xdir = (endP.x-curP.x)!=0 ? (endP.x-curP.x)/abs(endP.x-curP.x) : 0;
        ydir = (endP.y-curP.y)!=0 ? (endP.y-curP.y)/abs(endP.y-curP.y) : 0;

        if( rand()%100>=probability )
            xdir = replaceZero(xdir) ;
        if( rand()%100>=probability )
            ydir = replaceZero(ydir) ;

        if( xdir!=0 && median( tlCorner.x, curP.x+xdir, brCorner.x ) == curP.x+xdir && maze->array2D[curP.x+xdir][curP.y]!=c ){
            curP.x += xdir;
            numSteps++;
        }

        maze->array2D[curP.x][curP.y] = c;

        if( abs(curP.x-endP.x)+abs(curP.y-endP.y)<=1 )
            break;

        if( ydir!=0 && median( tlCorner.y, curP.y+ydir, brCorner.y ) == curP.y+ydir && maze->array2D[curP.x][curP.y+ydir]!=c ){
            curP.y += ydir;
            numSteps++;
        }

        maze->array2D[curP.x][curP.y] = c;
    }
    maze->array2D[endP.x][endP.y] = c;
    *presult = PATH_FOUND;
    return numSteps+abs(curP.x-endP.x)+abs(curP.y-endP.y);
}

int replaceZero( int dir ){
    if( dir==0 )
        dir = rand()%2 ? 1 : -1;
    return -dir;
}

/* Returns ture if the points x and y coordinates differ by no more than 1 */
bool adjacent( Point2D p1, Point2D p2 ){
    return (abs(p1.x-p2.x) + abs(p1.y-p2.y))<2;
}

int median( int a, int b, int c ){
        return a+b+c-min(min(a,b),c)-max(max(a,b),c);
}

int min( int a, int b ){
    if( a<=b )
        return a;
    else
        return b;
}

int max( int a, int b ){
    if( a>=b )
        return a;
    else
        return b;
}
