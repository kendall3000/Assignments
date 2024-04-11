#ifndef _event_h
#define _event_h
#include <stdbool.h>
#include "queue.h"
#include "road.h"
typedef enum eventType{ ADD_CAR_EVENT, PRINT_ROADS_EVENT } eventType;
typedef struct Event
{
    bool isNextSpaceEmpty;
    int cyclesUntilGreen;
    int cyclePrint;     //WHEN TO DO THING
    eventType whatDo;
}  Event;
#endif