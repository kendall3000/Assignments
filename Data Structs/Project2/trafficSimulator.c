#include "trafficSimulator.h"

/* Function declarations: */
TrafficData* readTrafficDataFromInputFile( char* name );

/* printNames
 * input: none
 * output: none
 *
 * Prints names of the students who worked on this solution
 */
void printNames( )
{
    /* TODO : Fill in you and your partner's names (or N/A if you worked individually) */
    printf("This solution was completed by:\n");
    printf("<student name #1>\n");
    printf("<student name #2 (if no partner write \"N/A\")>\n");
}


/* trafficSimulator
 * input: char* name of file to read
 * output: N/A
 *
 * Read in the traffic data from the file whose name is stored in char* filename
 * Simulate the rules outlined in the project 2 description
 */
void trafficSimulator( char* filename )
{
    /* TODO: complete this function */

    /* Read in the traffic data from filename.  It's recommended you call readTrafficDataFromInputFile to do this: */
    TrafficData* tData = readTrafficDataFromInputFile( filename );

    /* Loop until all events processed and either all cars reached destination or gridlock has occurred */

        /* Update the state of every traffic light */

        /* Loop on events associated with this time step */

        /* First try to move cars through the next intersection */

        /* Second move waiting cars onto the end of each road if possible */

        /* Third move cars forward on every road (only those that haven't moved yet this time step) */

}

/* readTrafficDataFromInputFile
 * input: char* filename of file to read
 * output: TrafficData* which stores the data of this road network
 *
 * Create a new TrafficData variable and read in the traffic data from the file whose name is stored in char* filename
 */
TrafficData* readTrafficDataFromInputFile( char* filename )
{
    /* open the file */
    FILE *pFile = fopen( filename, "r" );
    
    /* Optional TODO: read in all the data in pFile */
    /* HINT: use fscanf( pFile, "%d", &<your int variable here> ) to read an int from pFile */
    
    /* HINTs:
     * Each road can be stored in a `RoadData` struct (see `road.h`).
     *
     * You'll want to store all of these `RoadData` structs in a single array.  This is important to track the order that  
     * roads were added to your graph.  These are also the order they are processed in each time step.  You can store this
     * array in your TrafficData struct.
     *
     * You'll add edges to a graph to represent each road using `setEdge` (see `graph.c`).  The vertices of the graph 
     * represent intersections.  The graph will do the work of finding shortest paths (see `getNextOnShortestPath` in graph.c 
     * and the longest shortest path problem on Blackboard).
     *
     * It will also help to add your `RoadData` structs to your graph using `setEdgeData` (see `graph.c`).   You can then 
     * retrieve that `RoadData` struct by calling `getEdgeData`.  This will be helpful for finding roads when cars pass 
     * through intersections.
     * 
     * Each event will be stored in an Event struct (see `event.h`).
     * 
     * It's recommended to store all of the `Event` structs in a single priority queue (using time step as the priority).  This 
     * allows you to quickly find the next event to execute by time step (see `enqueueByPriority`, `getFrontPriority`, and 
     * `dequeuePQ`).
     *
     * Each car is stored in a Car struct (see `car.h`).
     */
    
    
    /* close file */
    fclose( pFile );

    return NULL; /* Optional TODO: Replace this with your TrafficData pointer */
}

