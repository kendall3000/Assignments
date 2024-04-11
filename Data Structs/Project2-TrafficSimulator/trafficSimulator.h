     #ifndef _trafficSimulator_h
    #define _trafficSimulator_h
    #include <stdlib.h>
    #include <stdio.h>
    #include <stdbool.h>
    #include <string.h>
    #include <time.h>
    #include <ctype.h>
    #include "graph.h"
    #include "queue.h"
    #include "priorityQueue.h"
    #include "event.h"
    #include "road.h"
    typedef struct trafficSimData
    {
        int iCycles;
        Event check;
        int iNumCarSteps;
        int sinceLastMove;
        RoadData **edgeStuff;
        int longestLightCycle;
        int iGraphSize;
        int iNumEdges;
        int iNumPrintCommands;
        //int maxCarinAdd;
        //Car **carStuff;     //need free
        //bool isGridLock;
        //Optional TODO - Fill this struct in with the data needed to simulate
        /* graph representing the road network */
        /* array of the roads of the graph in the sequence they were added to the graph */
        /* priority queue of events where the priority represents the time the event will occur */
        /* track the number of cars still in the simulator */
        /* track the longest number of time steps that any light takes to cycle around */
    }  trafficSimData;

    void printNames( );
    void trafficSimulator( char* filename );
    void fillGraph(Graph *g, int size, FILE *in_file, trafficSimData *data, int iNumEdges);
    void addCars(Graph *g, FILE *in_file, trafficSimData *data, PriorityQueue *printQueue);
    void fillPrintData(FILE *in_file, trafficSimData *data, PriorityQueue *printQueue);
    void runOneCycle(Graph *g, trafficSimData *data, PriorityQueue *printQueue);
    int carsOnRoad(Graph *g, trafficSimData *data, int iRoad);
    bool roadClear(Graph *g, trafficSimData *data, int iSize, int iNumEdges);
    bool isGridLock(Graph *g, trafficSimData *data);
    void addCarEvent(trafficSimData *data, Graph *g, PriorityQueue *printQueue);
    void printEvent(trafficSimData *data, Graph *g, PriorityQueue *printQueue);
    void freeData(Graph *g, trafficSimData *data, PriorityQueue *printQueue);
#endif