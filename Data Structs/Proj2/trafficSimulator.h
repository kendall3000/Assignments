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

typedef struct TrafficSimData
{
    //Optional TODO - Fill this struct in with the data needed to simulate traffic.  Suggested data:
    /* graph representing the road network */
    Graph * trafficGraph;

    /* array of the roads of the graph in the sequence they were added to the graph */
    RoadData ** roads;
    int numRoads;

    /* priority queue of events where the priority represents the time the event will occur */
    PriorityQueue *events;

    /* track the number of cars still in the simulator */
    int currentCarsActive;

    /* track the longest number of time steps that any light takes to cycle around */
    int longestLightCycle;

    int *printCommandSteps;
    double averageCounter;
    int maxStepsToDest;
    int iCycles;
    Event check;
    int iNumCarSteps;
    int sinceLastMove;
    RoadData **edgeStuff;
    int longestLightCycle;
    int iGraphSize;
    int iNumEdges;
    int iNumPrintCommands;

}  TrafficSimData;

void trafficSimulator( char* filename );
TrafficSimData *readTrafficData(char* filename);

#endif
