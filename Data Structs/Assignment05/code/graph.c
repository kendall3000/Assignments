#include "graph.h"

pqType createPQtype( graphType gt, int priority );
int getIndex( Graph* g, graphType p );
long minLong( long a, long b );

/* create
 * input: an int representing the maximum number of vertices needed in your graph
 * output: a pointer to a Graph (this is malloc-ed so must be freed eventually)
 *
 * Creates a new empty Graph and returns a pointer to it.  The maximum number of vertices is set to capacity.
 */
Graph* createGraph( int capacity, adjType type )
{
    int i,j;
    Graph* g = (Graph*)malloc(sizeof(Graph));
    g->vertexArray = (Vertex*)malloc(sizeof(Vertex)*capacity);
    g->vertexTable = createTableType( capacity, FIBONACCI_HASH, false );
    g->type = type;
    g->adjacencyMatrix = (int**)malloc(sizeof(int*)*capacity);
    g->pathsArray = (int**)malloc(sizeof(int*)*capacity);
    g->distance = (int**)malloc(sizeof(int*)*capacity);

    for( i=0; i<capacity; i++ ){
        g->adjacencyMatrix[i] = (int*)malloc(sizeof(int)*capacity);
        g->pathsArray[i] = (int*)malloc(sizeof(int)*capacity);
        g->distance[i] = (int*)malloc(sizeof(int)*capacity);
    }

    for( i=0; i<capacity; i++ ){
        for( j=0; j<capacity; j++ ){
            g->adjacencyMatrix[i][j] = -1;
            g->pathsArray[i][j] = -1;
            g->distance[i][j] = -1;
        }
    }

    g->numVertices = 0;
    g->capacity = capacity;
    g->changed = true;
    return g;
}

/* freeGraph and freeAdjList
 * input: a pointer to a Graph
 * output: none
 *
 * frees the given Graph and all of it's Vertex elements
 */
void freeGraph( Graph* g )
{
    int i;

    if( g==NULL ){
        printf("ERROR - freeGraph - Attempt to free NULL Graph pointer\n");
        exit(-1);
    }

    for( i=0; i<g->capacity; i++ ){
        free(g->adjacencyMatrix[i]);
        free(g->pathsArray[i]);
        free(g->distance[i]);
    }

    free( g->adjacencyMatrix );
    free( g->pathsArray );
    free( g->distance );

    /* Free vertex table */
    freeTable( g->vertexTable );

    /* Free vertex array */
    free( g->vertexArray );
    free( g );
}

/* addVertex
 * input: a pointer to a Graph, a graphType p
 * output: none
 *
 * adds a new vertex to the graph with its data set to p
 */
void addVertex( Graph* g, graphType p ){
    int i = getIndex( g, p );
    if( g->numVertices==g->capacity ){
        printf("ERROR - addVertex - Attempt to add more vertices than the capacity of the graph\n");
        exit(-1);
    }

    /* Check if vertex already in graph */
    if( i!=-1 ){
        printf("WARNING - addVertex - Attempt to add same graphType to graph multiple times\n");
        return;
    }

    g->vertexArray[g->numVertices].data = p;
    g->vertexArray[g->numVertices].index = g->numVertices;
    g->vertexArray[g->numVertices].visited = false;

    insertTable( g->vertexTable, getKey( p ), &g->vertexArray[g->numVertices] );

    g->vertexArray[g->numVertices].currentSuccessorIndex = -1;
    g->vertexArray[g->numVertices].currentPredecessorIndex = -1;

    g->numVertices++;
    g->changed = true;
}

/* isVertex
 * input: a pointer to a Graph, a graphType p
 * output: a bool
 *
 * returns true if the given graphType is contained in the graph
 */
bool isVertex( Graph* g, graphType p ){
    return getIndex( g, p )!=-1;
}

/* getVertexByIndex
 * input: a pointer to a Graph, an int, a pointer to a graphType
 * output: a bool
 *
 * finds index-th vertex added to the graph and inserts into next.  It returns true if this search was successful and false otherwise.
 */
bool getVertexByIndex( Graph* g, int index, graphType* next ){
    if( index>=g->numVertices )
        return false;
    *next = g->vertexArray[index].data;
    return true;
}

/* getIndex
 * input: a pointer to a Graph, a graphType
 * output: a bool
 *
 * finds index-th vertex added to the graph and inserts into next.  It returns true if this search was successful and false otherwise.
 */
int getIndex( Graph* g, graphType p ){
    Vertex* v = (Vertex *)searchTable( g->vertexTable, getKey(p) );
    if( v==NULL )
        return -1;
    return v->index;
}

/* setEdge
 * input: a pointer to a Graph, two graphType variables, a int
 * output: none
 *
 * Sets the specified edge in the graph to the int value
 */
void setEdge( Graph* g, graphType p1, graphType p2, int value )
{
    int i = getIndex( g, p1 );
    int j = getIndex( g, p2 );

    /* Add vertices if they're not already in graph */
    if( i==-1 ){
        addVertex( g, p1 );
        i = getIndex( g, p1 );
    }
    if( j==-1 ){
        addVertex( g, p2 );
        j = getIndex( g, p2 );
    }
    g->changed = true;
    g->adjacencyMatrix[i][j] = value;
}

/* getEdge
 * input: a pointer to a Graph, two graphType variables
 * output: a int
 *
 * Returns whether the specified edge is in the graph
 */
int getEdge( Graph* g, graphType p1, graphType p2 )
{
    int i = getIndex( g, p1 );
    int j = getIndex( g, p2 );

    /* Add vertices if they're not already in graph */
    if( i==-1 ){
        addVertex( g, p1 );
        i = getIndex( g, p1 );
    }
    if( j==-1 ){
        addVertex( g, p2 );
        j = getIndex( g, p2 );
    }

    return g->adjacencyMatrix[i][j];
}

/* getSuccessor
 * input: a pointer to a Graph, a graphType 'start', a pointer to a graphType 'pnext'
 * output: a bool and the next successor of start is stored at 'pnext'
 *
 * Finds the next node reachable from 'start'.  It stores the destination of this edge into location pointed to by 'pnext'.
 * If a successor exists it returns true and false otherwise.
 *
 * Ignores edges with values of -1 or INT_MAX.
 */
bool getSuccessor( Graph* g, graphType start, graphType* pnext )
{
    int i = getIndex( g, start );
    int j;


    /* Add vertices if they're not already in graph */
    if( i==-1 ){
        addVertex( g, start );
        i = getIndex( g, start );
    }
    else if( pnext==NULL ){
        printf("ERROR - getSuccessor - Attempt to call getSuccessor with NULL pnext\n");
        exit(-1);
    }

    Vertex* v = &g->vertexArray[i];

    j = v->currentSuccessorIndex;
    for( j=j+1; j<g->numVertices; j++ ){
        if( g->adjacencyMatrix[i][j]!=-1 && g->adjacencyMatrix[i][j]!=INT_MAX ){
            *pnext = g->vertexArray[j].data;
            v->currentSuccessorIndex = j;
            return true;
        }
    }
    v->currentSuccessorIndex = -1;
    return false;
}

/* getPredecessor
 * input: a pointer to a Graph, a graphType 'start', a pointer to a graphType 'pprev'
 * output: a bool and the next node with an edge going to start is stored at 'pprev'
 *
 * Finds the next node which has an edge going to 'start'.  It stores the destination of this edge into location pointed to by 'pprev'.
 * If a predecessor exists it returns true and false otherwise.
 */
bool getPredecessor( Graph* g, graphType start, graphType* pprev ){
    int i;
    int j = getIndex( g, start );


    /* Add vertices if they're not already in graph */
    if( j==-1 ){
        addVertex( g, start );
        j = getIndex( g, start );
    }
    else if( pprev==NULL ){
        printf("ERROR - getPredecessor - Attempt to call getSuccessor with NULL pprev\n");
        exit(-1);
    }

    Vertex* v = &g->vertexArray[j];

    i = v->currentPredecessorIndex;
    for( i=i+1; i<g->numVertices; i++ ){
        if( g->adjacencyMatrix[i][j]!=-1 ){
            *pprev = g->vertexArray[i].data;
            v->currentPredecessorIndex= i;
            return true;
        }
    }
    v->currentPredecessorIndex = -1;
    return false;
}

/* setVisited
 * input: a pointer to a Graph, a graphType, a bool value
 * output: none
 *
 * Sets the visited status of the vertex with the given graphType to 'value'
 */
void setVisited( Graph* g, graphType p, bool value ){
    int i = getIndex( g, p );

    /* Add vertices if they're not already in graph */
    if( i==-1 ){
        printf("WARNING - setVisited - Attempt to set visited for a graphType not in graph \n");
        addVertex( g, p );
        i = getIndex( g, p );
    }

    g->vertexArray[i].visited = value;
}

/* getVisited
 * input: a pointer to a Graph, a graphType
 * output: none
 *
 * Gets the visited status of the vertex with the given graphType
 */
bool getVisited( Graph* g, graphType p ){
    int i = getIndex( g, p );

    /* Add vertices if they're not already in graph */
    if( i==-1 ){
        printf("WARNING - getVisited - Attempt to get visited for a graphType not in graph \n");
        addVertex( g, p );
        i = getIndex( g, p );
    }

    return g->vertexArray[i].visited;
}

/* setDistance
 * input: a pointer to a Graph, two graphTypes, an int
 * output: none
 *
 * Sets the distance from the vertex 'from' to the vertex 'to' equal to 'dist'.
 */
void setDistance( Graph* g, graphType from, graphType to, int dist ){
    int i = getIndex( g, from );
    int j = getIndex( g, to );

    /* Add vertices if they're not already in graph */
    if( i==-1 ){
        printf("WARNING - getVisited - Attempt to set distance for a graphType not in graph \n");
        addVertex( g, from );
        i = getIndex( g, from );
    }
    if( j==-1 ){
        printf("WARNING - getVisited - Attempt to set distance for a graphType not in graph \n");
        addVertex( g, to );
        j = getIndex( g, to );
    }

    g->changed = true;

    g->distance[i][j] = dist;
}

/* getDistance
 * input: a pointer to a Graph, two graphTypes
 * output: an int
 *
 * Returns the stored distance from the vertex 'from' to the vertex 'to'.
 * If distance hasn't been set it returns a default value of -1
 */
int getDistance( Graph* g, graphType from, graphType to ){
    int i = getIndex( g, from );
    int j = getIndex( g, to );

    /* Add vertices if they're not already in graph */
    if( i==-1 ){
        printf("WARNING - getDistance - Attempt to get distance for a graphType not in graph \n");
        addVertex( g, from );
        i = getIndex( g, from );
    }
    if( j==-1 ){
        printf("WARNING - getDistance - Attempt to get distance for a graphType not in graph \n");
        addVertex( g, to );
        j = getIndex( g, to );
    }

    return g->distance[i][j];
}

/* dijkstrasAlg
 * input: a pointer to a Graph, a graphTypes
 * output: an int
 *
 * Finds the shortest path distance from the vertex 'from' to all over vertices in the graph
 * Assumes setEdge has been used to store the distance between adjacent pairs of points in the graph in the adjacency matrix.
 * If a vertex V is unreachable from start then it sets the distance to INT_MAX (i.e. setDistance( g, start, V, INT_MAX ); )
 */
void dijkstrasAlg( Graph* g, graphType start ){
    graphType next;
    pqType cur;
    int distance, i;

    PriorityQueue* q = createPQ();

    /* Set distance to all other points from start to INT_MAX (we relax this distance as we find better paths) */
    for( i=0; getVertexByIndex(g, i, &next); i++ )
        setDistance( g, start, next, INT_MAX );

    /* Set distance from the start point to itself to 0 (needed for algorithm below)*/
    setDistance( g, start, start, 0 );
    
    insertPQ( q, createPQtype(start,0) );
    /* Explore outwards from start.  We explore the closest vertices first (based on the getEdge value) */
    while( !isEmptyPQ(q) ){
        cur = removePQ( q );
        if( !getVisited( g, cur.info ) ){
            setVisited( g, cur.info, true );
            setDistance( g, start, cur.info, cur.priority );
            /* Get all of the neighbors of the current location.  Update their shortest paths from start if a better path has been found through cur. */
            while( getSuccessor(g, cur.info, &next) ) {;
                if( !getVisited( g, next ) && getDistance( g, start, next )> minLong((long)getDistance( g, start, cur.info )+getEdge( g, cur.info, next ),(long)INT_MAX)  ){
                    distance = getDistance( g, start, cur.info )+getEdge( g, cur.info, next );
                    setDistance( g, start, next, distance );
                    insertPQ( q, createPQtype( next, distance ) );
                }
            }
        }
    }

    freePQ( q );
}

pqType createPQtype( graphType gt, int priority ){
    pqType pqt;
    pqt.info = gt;
    pqt.priority = priority;
    return pqt;
}

long minLong( long a, long b ){
  if( a>b )
    return b;
  return a;
}
