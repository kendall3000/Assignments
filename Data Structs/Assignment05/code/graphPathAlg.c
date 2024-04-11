#include "graph.h"
#include "graphPathAlg.h"
//#include "queuePoint2D.h"
#include <limits.h>

/* printName
 * input: none
 * output: none
 *
 * Prints the name of the student who worked on this solution
 */
void printName( )
{
    /* TODO : Fill in your names */
    printf("This solution was completed by:\n");
    printf("<Kendall Ramos>\n");
}

/* OPTIONAL HELPER FUNCTION
 * buildGraph
 *
 * IMPORTANT NOTE: This is an entirely optional helper function which is only called by student implemented functions.
 * Creates a new graph to represent the given maze.  
 */
Graph* fillGraph( char** maze, int size)
{
    Graph *g = createGraph(size * size, MATRIX_TYPE);
    int i, j;
    for(i = 1; i < size - 1; i++)
        for(j = 1; j < size - 1; j++)
            if(maze[i][j] != 'X')
                addVertex(g, createPoint(j, i));
    for(i = 1; i < size - 1; i++)
    {
        for(j = 1; j < size - 1; j++)
        {
            if(isVertex(g, createPoint(j, i))) //CHECK LEFT, RIGHT, UP, DOWN FOR SPACES, IF SPACE, SETEDGE
            {
                if(isVertex(g, createPoint(j, i-1))) //BOOLS MAY BE IF VISITED AND NEED TO BE SET TO FALSE AT DECLARATION
                        setEdge(g, createPoint(j, i), createPoint(j, i-1), true);
                    if(isVertex(g, createPoint(j, i+1)))
                        setEdge(g, createPoint(j, i), createPoint(j, i+1), true);
                    if(isVertex(g, createPoint(j-1, i)))
                        setEdge(g, createPoint(j, i), createPoint(j-1, i), true);
                    if(isVertex(g, createPoint(j+1, i)))
                        setEdge(g, createPoint(j, i), createPoint(j+1, i), true);
                        }
                    }
}
return g; }
    /* hasPath
     * input: a **char pointer to a maze, an int that represents the side length of
    the maze
     * output: pathResult
     *
     * Detects whether a path exists from 'S' to 'F' in the graph ('X' marks
    impassable regions)
     */
    pathResult hasPath( char** maze, int mazeSize )
    {
        Point2D pStart = getPoint(maze, 'S', mazeSize);
        Point2D pFinish = getPoint(maze, 'F', mazeSize);
        Graph *g = fillGraph(maze, mazeSize);
        pathResult pCheck = checkPath(g, pStart, pFinish, mazeSize);
        freeGraph(g);
        return pCheck;
    }
    pathResult checkPath(Graph *g, Point2D pCurr, Point2D pFinish, int size)
    {
        setVisited(g, pCurr, true);
if(pCurr.x == pFinish.x && pCurr.y == pFinish.y)
    return PATH_FOUND;
if(isVertex(g, createPoint(pCurr.x + 1, pCurr.y)))
    if(getVisited(g, createPoint(pCurr.x + 1, pCurr.y)) == false)
if(checkPath(g, createPoint(pCurr.x + 1, pCurr.y), pFinish, size) == PATH_FOUND)
    return PATH_FOUND;
        if(isVertex(g, createPoint(pCurr.x, pCurr.y - 1)))
            if(getVisited(g, createPoint(pCurr.x, pCurr.y - 1)) == false)
                if (checkPath(g, createPoint(pCurr.x, pCurr.y - 1), pFinish, size)
    == PATH_FOUND)
                    return PATH_FOUND;
        if(isVertex(g, createPoint(pCurr.x - 1, pCurr.y)))
            if(getVisited(g, createPoint(pCurr.x - 1, pCurr.y)) == false)
                if (checkPath(g, createPoint(pCurr.x - 1, pCurr.y), pFinish, size)
    == PATH_FOUND)
                    return PATH_FOUND;
        if(isVertex(g, createPoint(pCurr.x, pCurr.y + 1)))
            if(getVisited(g, createPoint(pCurr.x, pCurr.y + 1)) == false)
                if (checkPath(g, createPoint(pCurr.x, pCurr.y + 1), pFinish, size)
    == PATH_FOUND)
                    return PATH_FOUND;
        return PATH_IMPOSSIBLE;
    }
    Point2D getPoint(char** maze, char val, int size)
{
int i, j;
        int x = 0;
        int y = 0;
        for(i = 0; i < size; i++)
        {
            for(j = 0; j < size; j++)
            {
                if(maze[i][j] == val)
                {
x = j;
y = i; }
} }
        return createPoint(x, y);
    }
    /* findNearestFinish
     * input: a **char pointer to a maze, an int that represents the side lengths of
    the maze, a pointer to an int
     * output: pathResult
     *
     * The maze contains one 'S' and multiple 'F's (1 or more).  'X' marks
    impassable regions.
     * Find the length of the shortest path to any 'F' from 'S' and return it in
    spDist.
     * If no 'F' is reachable set spDist to INT_MAX.
     */
    pathResult findNearestFinish( char** maze, int mazeSize, int *spDist )
    {
        Point2D pStart = getPoint(maze, 'S', mazeSize);
    Graph *g = fillGraph(maze, mazeSize);
    setDistance(g, pStart, pStart, 0);
    (*spDist) = INT_MAX;
    return searchBFT(g, pStart, spDist, maze);
}
pathResult searchBFT(Graph *g, Point2D pStart, int *spDist, char **maze)
{
    Queue *q = createQueue();
    enqueue(q, pStart);
    Point2D pTemp;
    Point2D pNext;
    setVisited(g, pStart, true);
    while(!isEmptyQueue(q))
    {
        pTemp = dequeue(q); //First run set to pStart.
        if(maze[pTemp.y][pTemp.x] == 'F')//i = y-axis, j == x-axis
        {
            (*spDist) = getDistance(g, pStart, pTemp);
            freeQueue(q);
            return PATH_FOUND;
        }
        while(getSuccessor(g, pTemp, &pNext))
        {
            if(!getVisited(g, pNext))
            {
                setVisited(g, pNext, true);
                int tempDist = getDistance(g, pStart, pTemp) + 1;

                setDistance(g, pStart, pNext, tempDist);
                enqueue(q, pNext);

} }
    }
    freeQueue(q);
    return PATH_IMPOSSIBLE;
}
/* findLongestSimplePath
     * input: a **char pointer to a maze, an int that represents the side lengths of
    the maze, a pointer to an int
     * output: pathResult
     *
     * The maze contains one 'S' and one 'F'.  'X' marks impassable regions.
     * Find the length of the longest simple path to 'F' from 'S' and return it in
    lpDist (simple paths are those that do not visit any vertex twice).
     * If 'F' is not reachable set lpDist to -1.
     */
    pathResult findLongestSimplePath( char** maze, int mazeSize, int *lpDist ){
        //TODO: Complete this algorithm
        Point2D pStart = getPoint(maze, 'S', mazeSize);
        Point2D pFinish = getPoint(maze, 'F', mazeSize);
        int tempDist = 0;
        Graph *g = fillGraph(maze, mazeSize);

    if(checkPath(g, pStart, pFinish, mazeSize) == PATH_FOUND)
    {
        if((*lpDist) < tempDist)
        {
}
        //Double for loop resetting all nodes visited status to false. void resetPath.
        //Recursive using getSuccessor, if only one unvisited, means it's a bottleneck, and can change current node to not exist, and return.
        //This will make the rest of the nodes unreachable in the bottleneck.
        //Recursively checking for if nodes are visited with viable paths.
        //Updating lpDist if greater than current lpdist, store old dist in temporary variable for loop
        //Do this in a while loop?
        //Using CheckVisited for loop call with a recursive function nested??
        //(*lpDist) = LENGTH OF PATH
        return PATH_FOUND;
}
    (*lpDist) = -1;
    return PATH_IMPOSSIBLE;
}
void resetPath(char **maze, int size, Graph *g)
{
    int i, j;
    for(i = 0; i < size; i++)
    for(j = 0; j < size; j++)
        if(isVertex(g, createPoint(j, i)))
            setVisited(g, createPoint(j, i), false);
}
int longestDistance(char** maze, int mazeSize, Graph *g, Point2D pStart, Point2D pFinish){
    int iRetVal = 0;
    return iRetVal;
}
bool checkVisited(Graph *g, int size)
{
    int i, j;
    bool bRet = true;
    for(i = 1; i < size - 1; i++)
        for(j = 1; j < size - 1; j++)
            if(isVertex(g, createPoint(j, i)))
                if(!getVisited(g, createPoint(j, i))){
                    bRet = false;
                    break; 
                }
    return bRet;
}
