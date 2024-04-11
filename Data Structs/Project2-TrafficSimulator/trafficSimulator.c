#include "trafficSimulator.h"
#include <stdio.h>
/* trafficSimulator
 * input: char* name of file to read
 * output: N/A
 *
 * Simulate the road network in the given file
 */
    /* Read in the traffic data.  You may want to create a separate function to do this. */
    //void trafficSimulator( char* filename )
    /* Loop until all events processed and either all cars reached destination or gridlock has occurred */
/* Loop on events associated with this time step */
/* First try to move through the intersection */
/* Second move cars forward on every road */
/* Third move cars onto road if possible */
void printNames( )
{
    /* TODO : Fill in you and your partner's names (or N/A if you worked individually) */
    printf("This solution was completed by:\n");
    printf("<student name #1>\n");
    printf("<student name #2 (if no partner write \"N/A\")>\n");
}
void trafficSimulator( char* filename )
{
    if(filename != NULL)
    {
        FILE *in_file = fopen(filename, "r");exit(-1); //Opening the file nand filling initial variables.
        if(in_file == NULL)
        {
            printf("File %s not found.\n", filename);
            exit(-1);
        }
            //int i, j;
            int iSize, iNumEdges;   //iSize is number of vertices
            PriorityQueue *printQueue = createPQ(); //For PRINTING
            //Queue *carQueue = createQueue(); //FOR CARS (MAYBE ARRAY OF QUEUES??)
            trafficSimData *data = malloc(sizeof(trafficSimData));
            fscanf(in_file, "%d %d", &iSize, &iNumEdges);
            data->iGraphSize = iSize;
            data->iNumEdges = iNumEdges;
            Graph *g = createGraph(iSize);
        fillGraph(g, iSize, in_file, data, iNumEdges);
        addCars(g, in_file, data, printQueue);
        fillPrintData(in_file, data, printQueue);
        data->iCycles = 0;
        data->sinceLastMove = 0;
        //data->isGridLock = false;
        //roadClear checking for if all roads are empty, meaning all cars reached dest.
        while(!isGridLock(g, data) && !isEmptyPQ(printQueue))//&& roadClear(g,data, iSize, iNumEdges))) //Maybe - 2?? //First: Check for gridlock
        {
            runOneCycle(g, data, printQueue);
            data->iCycles++;
            //***************TODO*****************
            //Event stuff
        }
        freeData(g, data, printQueue);
    }else {
        printf("No filename passed.\n");
        exit(-1);
    }
}

void runOneCycle(Graph *g, trafficSimData *data, PriorityQueue *printQueue)
{
int i, j;
    if(getNextPQ(printQueue)->cyclePrint == data->iCycles)
    {
        if(getNextPQ(printQueue)->whatDo == ADD_CAR_EVENT)
        {
            addCarEvent(data, g, printQueue);
            Event *throwData = dequeuePQ(printQueue);
            free(throwData);
            printf("\n");
        }
        if(getNextPQ(printQueue)->whatDo == PRINT_ROADS_EVENT)
        {
            printEvent(data, g, printQueue);
            Event *throwData = dequeuePQ(printQueue);
            free(throwData);
            printf("\n");
}
}
    for(i = 0; i < data->iNumEdges; i++)
        {
            if(data->edgeStuff[i]->whenLightOn == data->iCycles % data->edgeStuff[i]->whenLightCycle)   //SETTING LIGHTS
                data->edgeStuff[i]->isGreen = true;
            if(data->edgeStuff[i]->whenLightOff == data->iCycles % data->edgeStuff[i]->whenLightCycle)
            data->edgeStuff[i]->isGreen = false;
}
    /******TODO******
     * light priority at interesction
     * USE FINDSHORTESTPATH TO DETERMINE CARS NEXT ROAD IF AT INTERSECTION
     *
*/
    for(i = 0; i < data->iNumEdges; i++)    //MOVES CARS ALONG THEIR RESPECTIVE EDGES (ROADS)
    {
        if(data->edgeStuff[i]->dumpQueue == true) //ADDING TO THE FRONT OF THE ROAD
        {
            if(data->edgeStuff[i]->carSpots[0] == NULL)//CHECKING IF FRONT OF ROAD IS EMPTY
            {
                if(!isEmpty(data->edgeStuff[i]->carsInLine))
                    data->edgeStuff[i]->carSpots[0] = dequeue(data->edgeStuff[i]->carsInLine);
//TODO }
}
        for(j = 0; j < data->edgeStuff[i]->iLength - 1; j++)
            {
                if(data->edgeStuff[i]->carSpots[j] != NULL) //CAR IN THAT SPOT
                {
                    if(data->edgeStuff[i]->carSpots[j+1] == NULL && data->edgeStuff[i]->carSpots[j]->movedThisStep == false) //NEXT SPOT IS EMPTY
                    {
                        data->edgeStuff[i]->carSpots[j]->movedThisStep = true;
                        data->edgeStuff[i]->carSpots[j]->iCycles++;
                        data->edgeStuff[i]->carSpots[j+1] = data->edgeStuff[i]->carSpots[j]; //CAR MOVES FORWARD ONE SPACE
                        data->edgeStuff[i]->carSpots[j] = NULL; 
            data->edgeStuff[i]->carSpots[j+1]->iRoadLocation = j + 1;
            data->sinceLastMove = 0;
        }
} }
                if(data->edgeStuff[i]->carSpots[j+1] != NULL && data->edgeStuff[i]->carSpots[j]->movedThisStep == false) //IF AT END OF PATH
                {
                    int nextRoad;
                    if(getNextOnShortestPath(g, data->edgeStuff[i]->carSpots[j+1]->initStart, data->edgeStuff[i]->carSpots[j+1]->initDest, &nextRoad)) //FINDS CARS NEXT PATH
                    {
                        if(data->edgeStuff[nextRoad]->carSpots[0] == NULL && data->edgeStuff[nextRoad]->isGreen == true) //IF LIGHT IS GREEN
                        {
                            data->edgeStuff[nextRoad]->carSpots[0] = data->edgeStuff[i]->carSpots[j+1];
                            data->edgeStuff[i]->carSpots[j+1] = NULL;
                        }
} 
}

}
    for(i = 0; i < data->iNumEdges; i++)    //MOVES CARS ALONG THEIR RESPECTIVE EDGES (ROADS)
    {
        for(j = 0; j < data->edgeStuff[i]->iLength; j++)
            {
                if(data->edgeStuff[i]->carSpots[j] != NULL) //CAR IN THAT SPOT
                    data->edgeStuff[i]->carSpots[j]->movedThisStep = false;
} }
    //CAR MOVEMENT STUFF HERE
} /*
} */
for(j = 0; j < tempRoad.iLength - 1; j++)
{
    if(tempRoad.carSpots[j] != NULL) //CAR IN THAT SPOT
        if(tempRoad.carSpots[j+1] == NULL) //NEXT SPOT IS EMPTY
        {
            tempRoad.carSpots[j+1] = tempRoad.carSpots[j]; //CAR MOVES FORWARD ONE SPACE
tempRoad.carSpots[j] = NULL;
    data->sinceLastMove = 0;
}
    bool isGridLock(Graph *g, trafficSimData *data){
        int lastMove = data->sinceLastMove;
        int longestLight = data->longestLightCycle;
        if(lastMove == longestLight + 1){
            return true;
        }
        return false;
    }
    bool roadClear(Graph *g, trafficSimData *data, int iSize, int iNumEdges)
{
int i;
        for(i = 0; i < iNumEdges; i++)
        {
            if(!isEmpty(data->edgeStuff[i]->carsInLine))
                return false;
            //Checking all roads (edges) for if their car queue is empty, if atleast one is not empty, 
            return false;
            //Use getsuccessor on each road vertice from 0 - iSize
            //RoadData road = getEdgeData(g, )
        }
        return true;
    }
}
}
    void addCarEvent(trafficSimData *data, Graph *g, PriorityQueue *printQueue)
{
    int i;
        for(i = 0; i < data->iNumEdges; i++)
    {
        if(data->edgeStuff[i]->startAdd == data->iCycles)
        {
            data->edgeStuff[i]->dumpQueue = true;
            printf("CYCLE %d - ADD CAR EVENT - Cars enqueued on road from %d to %d\n", data->edgeStuff[i]->startAdd, data->edgeStuff[i]->iFromVertex, data->edgeStuff[i]->iToVertex);
        }
} }
void printEvent(trafficSimData *data, Graph *g, PriorityQueue *printQueue)
{
//TODO
    int i, j, iNext;
    printf("CYCLE %d - PRINT_ROAD_EVENT - CURRENT CONTENTS OF THE ROADS:\n",
data->iCycles);
    for(i = 0; i < data->iNumEdges; i++)
    {
        while(getSuccessor(g, i, &iNext))
        {
            RoadData *roadInfo = getEdgeData(g, i, iNext);
            printf("Cars on the road from %d to %d:\n", i, iNext);
            for(j = 0; j < roadInfo->iLength; j++)
            {
                if(roadInfo->carSpots[j] == NULL)
                    printf("-");
                else if(roadInfo->carSpots[j] != NULL)
                    printf("%d", roadInfo->carSpots[j]->finalDestination);
}
            printf("\n");
        }
//STUFF
} }
int carsOnRoad(Graph *g, trafficSimData *data, int iRoad){
    int i;
    int numCars = 0;
    for(i = 0; i < data->edgeStuff[iRoad]->iLength; i++)
    {
        if(data->edgeStuff[iRoad]->carSpots[i] != NULL)
}
numCars++;
        return numCars;
}
}
    void fillGraph(Graph *g, int size, FILE *in_file, trafficSimData *data, int iNumEdges)

{
int i, j;
    int iToVertex, iNumRoads;
    int iFromVertex, iConnRoadLength;
    int k = 0;
    data->longestLightCycle = 0;
    data->edgeStuff = malloc(sizeof(RoadData*) * iNumEdges);
    for(i = 0; i < size; i++)
    {
        fscanf(in_file, "%d %d", &iToVertex, &iNumRoads);
        //addVertex(g, iToVertex); //Final destination, iNumRoads is connecting "to" roads to that intersection
        //set edges and vertexes of to and from
        //RoadData *roadStuff = malloc(sizeof(RoadData) * iNumRoads);
        for(j = 0; j < iNumRoads; j++)//getting the roads to be connected as it reads through
        {
            RoadData *tempRoad = malloc(sizeof(RoadData));
            fscanf(in_file, "%d %d %d %d %d", &iFromVertex, &iConnRoadLength, &tempRoad->whenLightOn, &tempRoad->whenLightOff, &tempRoad->whenLightCycle);
                tempRoad->iToVertex = iToVertex;
                tempRoad->iFromVertex = iFromVertex;
                tempRoad->iLength = iConnRoadLength;
                if(tempRoad->whenLightCycle > data->longestLightCycle)
                    data->longestLightCycle = tempRoad->whenLightCycle;
                tempRoad->carSpots = malloc(sizeof(Car*) * tempRoad->iLength);
                tempRoad->carsInLine = createQueue();
                tempRoad->dumpQueue = false; //if true, add one car onto road per
                //addVertex(g, iFromVertex);
                setEdge(g, iFromVertex, iToVertex, iConnRoadLength);
                setEdgeData(g, iFromVertex, iToVertex, tempRoad);
                data->edgeStuff[k] = tempRoad;
                k++;
}
            //maybe free roadStuff inside i loop??
        }
}
    void addCars(Graph *g, FILE *in_file, trafficSimData *data, PriorityQueue *printQueue)
{
int i, j;
        int numCarsinCycle;
        //data->maxCarinAdd = 0;
        //Maybe 2d array to scan into?
        //STORE IN PQ???
        fscanf(in_file, "%d", &data->iNumCarSteps); //SCANNING STARTING LINE 34, NUMBER OF I REPEATS, NUMBER OF STEPS TO ADD CARS (WHICH CYCLES TO ADD)
        //data->carStuff = malloc(sizeof(*data->carStuff) * data->iNumCarSteps);

    for(i = 0; i < data->iNumCarSteps; i++)
    {
        Car *tempCar = malloc(sizeof(Car));
        fscanf(in_file, "%d %d %d", &tempCar->initStart, &tempCar->initDest, &tempCar->timeStepToAdd); 
        car
fscanf(in_file, "%d", &numCarsinCycle);
//if(numCarsinCycle > data->maxCarinAdd)
//    data->maxCarinAdd = numCarsinCycle;
tempCar->iCycles = 0;
tempCar->movedThisStep = false;
//Car *iCars = malloc(sizeof(Car) * numCarsinCycle);
for(j = 0; j < numCarsinCycle; j++)
{
    fscanf(in_file, "%d", &tempCar->finalDestination); //movements of
    Event *carEvent = malloc(sizeof(Event));
    carEvent->whatDo = ADD_CAR_EVENT;
                getEdgeData(g, tempCar->initStart, tempCar->initDest)->startAdd = tempCar->timeStepToAdd;
                enqueue(getEdgeData(g, tempCar->initStart, tempCar->initDest)->carsInLine, tempCar);
                enqueueByPriority(printQueue, carEvent, tempCar->timeStepToAdd);
                //READ ME ***********************************************************************
                //ENQUEUE IN GRAPH AT EDGE NUMBER OF INITSTART
} }
}
    void fillPrintData(FILE *in_file, trafficSimData *data, PriorityQueue
    *printQueue)
    {
        int i;
        int iNumCommands;
        int cycleToPrint;
        fscanf(in_file, "%d", &iNumCommands);
        data->iNumPrintCommands = iNumCommands;
        //data->printCommands = malloc(sizeof(int) * iNumCommands);
        for(i = 0; i < iNumCommands; i++)
        {
            Event *printData = malloc(sizeof(Event));
            printData->whatDo = PRINT_ROADS_EVENT;
            fscanf(in_file, "%d", &cycleToPrint);
            printData->cyclePrint = cycleToPrint;
        enqueueByPriority(printQueue, printData, cycleToPrint);
    }
}
void freeData(Graph *g, trafficSimData *data, PriorityQueue *printQueue)
{
    int i;
    freePQ(printQueue);
    for(i = 0; i < data->iNumEdges; i++)
    {
        free(data->edgeStuff[i]->carSpots);
        freeQueue(data->edgeStuff[i]->carsInLine);
    }
    free(data);
    freeGraph(g);
}