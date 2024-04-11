#include <stdlib.h>

#include "multilevelQueueScheduler.h"

void attemptPromote( schedule *ps );
int min( int x, int y );

static const int STEPS_TO_PROMOTION = 50;
static const int FOREGROUND_QUEUE_STEPS = 5;

/* printNames
 * input: none
 * output: none
 *
 * Prints names of the students who worked on this solution
 */
void printNames( )
{
    /* TODO : Fill in you and your partner's names (or N/A if you worked individually) */
    printf("\nThis solution was completed by:\n");
    printf("<Kendall Ramos>\n");
    printf("<\"N/A\">\n\n");
}

/* createSchedule
 * input: none
 * output: a schedule
 *
 * Creates and return a schedule struct.
 */
schedule* createSchedule( ) {
        /* TODO: initialize data in schedule */
        schedule *ps = (schedule*)malloc(sizeof(schedule));
        ps->foreQueue= createQueue();
        ps->backQueue = createQueue();
        ps->totalTimeSteps = 0;
        return ps; /* TODO: Replace with your return value */
    }
    /* isScheduleUnfinished
     * input: a schedule
     * output: bool (true or false)
     *
     * Check if there are any processes still in the queues.
     * Return TRUE if there is.  Otherwise false.
     */
    bool isScheduleUnfinished( schedule *ps ) {
        /* TODO: check if there are any process still in a queue.  Return TRUE if
there is. */
        return !isEmpty(ps->foreQueue) || !isEmpty(ps->backQueue); /* TODO:
    Replace with your return value */
    }
    /* addNewProcessToSchedule
     * input: a schedule, a string, an int, a priority
     * output: void
     *
     * Create a new process with the provided name, runtime, and priority.
     * Add that process to the appropriate queue
     */
    void addNewProcessToSchedule( schedule *ps, char *processName, int runtime, priority p ) {
        /* TODO: complete this function.
        The functions "initializeProcessData" in processSimulator.c will be useful
    in completing this. */
        processData *proc;
        proc = initializeProcessData(processName);
        ps->backQueue->qFront->qt->processName = processName;
        ps->backQueue->qFront->qt->data = proc;
        ps->backQueue->qFront->qt->pry = p;
        ps->backQueue->qFront->qt->timeSteps = runtime;
        ps->backQueue->qFront->qt->atHead = 0;
        ps->backQueue->qFront->qt->timeStepsTaken = 0;
        ps->backQueue->qFront->qt->addedToBackground = ps->totalTimeSteps;
    free( processName ); /* TODO: This is to prevent a memory leak but you should remove it once you create a process to put processName into */
}
char* runNextProcessInSchedule( schedule *ps ) {

    char *ret = NULL;
    int numSteps;
    
    attemptPromote( ps ); /* This will call your attemptPromote code. */
    
    numSteps = 0; /* TODO: Replace 0 with the number of steps the next process should be run for.  It may help to use min. */
    
    /* TODO: Delete the following printf once you get the infinite loop fixed */
    printf("IMPORTANT NOTE: There will be an infinite loop in runNextProcessInSchedule if you get isScheduleUnfinished and addNewProcessToSchedule working correctly\n"); 
    /* TODO: Uncomment the code below to dequeue elements from the two Queues and break your code out of the infinite loop.*/
    
    if( !isEmpty(ps->foreQueue) )
        dequeue(ps->foreQueue);
    else if( !isEmpty(ps->backQueue) )
        dequeue(ps->backQueue);
    
    return ret;
    /* your call to runProcess will look something like this: */
    //bool b = runProcess( /* name of process */, &ret, &numSteps );
        /* TODO: complete this function.
        The function "runProcessForOneTimeStep", "promoteProcess", and
    "freeProcessData"
        in processSimulator.c will be useful in completing this. */
        queueType qt;
        ps->totalTimeSteps++;
        if(ps->totalTimeSteps - ps->backQueue->qFront->qt->addedToBackQueue > 50)
            enqueue(ps->foreQueue, dequeue(ps->backQueue));
        if(!isEmpty(ps->foreQueue)) {
            runProcessForOneTimeStep(ps->foreQueue->qFront->qt->processName, &ps->foreQueue->qFront->qt->data);
            ps->foreQueue->qFront->qt->timeStepsTaken++;
            ps->foreQueue->qFront->qt->atHead++;
            if(ps->foreQueue->qFront->qt->timeStepsTaken >= ps->foreQueue->qFront->qt->timeSteps) {
/*
                queueType qt was created so that after dequeue'ing occured the
    processData could be
                freed before the dequeued element was freed
                */
                qt = dequeue(ps->foreQueue);
                freeProcessData(&ps->foreQueue->qFront->qt->data);
                free(qt);
            }
            else if(ps->foreQueue->qFront->qt->atHead == 5) {
                ps->foreQueue->qFront->qt->atHead = 0;
                enqueue(ps->foreQueue, dequeue(ps->foreQueue));
            }
} else {
            if(ps->backQueue->qFront->qt->timeStepsTaken >= ps->backQueue->qFront->qt->timeSteps) {
                qt = dequeue(ps->backQueue);
                freeProcessData(&ps->backQueue->qFront->qt->data);
                free(qt);
} else {
                runProcessForOneTimeStep(ps->backQueue->qFront->qt->processName,
    &ps->backQueue->qFront->qt->data);
} }
        return ret; /* TODO: Replace with your return value */
    }
    /* freeSchedule
     * input: a schedule
     * output: none
     *
     * Free all of the memory associated with the schedule.
     */
    void freeSchedule( schedule *ps ) {
        /* TODO: free any data associated with the schedule.
        the function "freeQueue" in queue.c will be useful in completing this.
        You may also want to call "freeProcessData" for any processes still left in
    your queues */
        queueType qt;
    while(!isEmpty(ps->foreQueue)) {
        qt = dequeue(ps->foreQueue);
        freeProcessData(&ps->foreQueue->qFront->qt->data);
        free(qt);
    }
    while(!isEmpty(ps->backQueue)) {
        qt = dequeue(ps->backQueue);
        freeProcessData(&ps->backQueue->qFront->qt->data);
        free(qt);
    }
    freeQueue(ps->foreQueue);
    freeQueue(ps->backQueue);
    freeSchedule(ps);
}


/* PROVIDED FUNCTION
 * freeSchedule
 * input: two ints
 * output: the smaller of the 2 ints
 */
int min( int x, int y ){
    if( x<y )
        return x;
    return y;
}
