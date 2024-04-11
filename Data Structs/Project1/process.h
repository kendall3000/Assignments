#ifndef _process_h
#define _process_h

typedef enum priority { FOREGROUND, BACKGROUND } priority; 

/* DO NOT directly access any data inside of a processData struct */
typedef struct processData{ int heap[  30        ]; char       PN21[       21];char TLN        [4  ];}   processData ;

/* struct process (only accessed in student written code)
 *
 * The data associated with a specific process.
 * At minimum you need to track the process name,
 * and a pointer to the processData struct returned 
 * by initializeProcessData,
 *
 * Hint: It may help to store how many time steps happened 
 * before a process was added to the schedule.
 *
 * You may also want to track the number of steps remaining until 
 * your FOREGROUND process is moved to the back of the queue.
 */
typedef struct process
{
    //TODO: Put the data for your process here!
    char* processName;
    int stepsUntilComplete;
    priority p;
    int stepsUntilEvicted;
    int stepWhenAddedToQueue;
    processData* data;
    char *processName;
    int stepsUntilComp;
    int *totalSteps;
    processData *proData;
    priority priority1;
    int stepsOver;
    int waitTime;
    int timeSteps;
    int atHead;
    int timeStepsTaken;
    int pry;
    int addedToBackground;
    int addedToBackQueue;

}  process;

#endif

