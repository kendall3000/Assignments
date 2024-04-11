#ifndef _road_h
#define _road_h
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
 
#include "car.h"
#include "queue.h"
typedef struct RoadData
{
   int iLength;
   int whenLightOn;
   int whenLightOff;
   int whenLightCycle;   //
   int iToVertex;
   int iFromVertex;
   Car **carSpots; //array for car location CHNGE TO CAR ARRAY
   bool isGreen;
   Queue *carsInLine;
   int startAdd;
   bool dumpQueue;
   //Queue *carsinLine;
   //int iIncomingRoads[];
   /* TODO - Add data associated with road.  Suggested data: */
   /* length of this road */
   /* information used to record/update whether the light at the end of this
road is green or red */
   /* intersections this road starts from and moves to */
   /* array of cars associated with this road */
   /* queue of cars waiting to enter this road */
}  RoadData;
 
void printCar();
#endif
