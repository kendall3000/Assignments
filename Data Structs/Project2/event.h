#ifndef _event_h
#define _event_h
#include <stdbool.h>

#include "queue.h"
#include "road.h"

typedef enum eventType{ ADD_CAR_EVENT, PRINT_ROADS_EVENT } eventType;

typedef struct Event
{
    //TODO:  Add information associated with the different events of your simulation.

    /* It may be useful to store a queue of cars.  While this isn't needed for print road events, it is
     * useful for your add car events so they can store the cars waiting to be added to the simulation at the specified time 
     * step.  The `queue.h` function `mergeQueues` can be used to easily move these cars into the waiting queue of their 
     * associated road at the specified time step.
     */
    bool isNextSpaceEmpty;
    int cyclesUntilGreen;
    int cyclePrint;    
    eventType whatDo;

}  Event;


#endif
