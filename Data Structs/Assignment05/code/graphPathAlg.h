#ifndef _graphPathAlg_h
#define _graphPathAlg_h
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "graph.h"
#include "point2D.h"
#include "stackPoint2D.h"
#include "queuePoint2D.h"
#include "priorityQueuePoint2D.h"
#include "array2D.h"

typedef enum pathResult{ PATH_IMPOSSIBLE, PATH_FOUND, PATH_UNKNOWN } pathResult;

void printName( );

/*pathResult hasPath( array2D *maze );*/
pathResult findNearestFinish( char** maze, int mazeSize, int *spDist );
pathResult findTunnelRoute( array2D *maze, int k );


typedef struct MazeData
{
    Point2D *pStart;
    Point2D *pFinish;
    char** maze;
    Graph *g;

}  MazeData;

pathResult hasPath( char** maze, int mazeSize );
Graph* fillGraph( char** maze, int size);
bool isPathNaiveRec( Graph* g, Point2D startP, Point2D endP, int maxPathLength );
void isPathWarshall( Graph* g );
Point2D getPoint(char** maze, char val, int size);
pathResult checkPath(Graph *g, Point2D pCurr, Point2D pFinish, int size);
bool checkVisited(Graph *g, int size);
pathResult searchBFT(Graph *g, Point2D pStart, int *spDist, char **maze);
int longestDistance(char** maze, int mazeSize, Graph *g, Point2D pStart, Point2D pFinish);

#endif
