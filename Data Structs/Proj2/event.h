#ifndef _event_h
#define _event_h
#include <stdbool.h>

#include "queue.h"
#include "road.h"

typedef enum eventType{ ADD_CAR_EVENT, PRINT_ROADS_EVENT } eventType;

typedef struct Event
{
    //TODO:  Add information associated with the different events of your simulation.
    // adding cars to road
    // from vertex
    int starting;
    
    // to vertex
    int ending;

    // destination
    int destinationVertex;

    // time step to add event
    int whenToAddCar;

    // int cycleCarJoined;

}  Event;


#endif
