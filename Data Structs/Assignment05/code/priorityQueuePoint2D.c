#include "priorityQueuePoint2D.h"

/*
 * Default starting size for the PriorityQueue
 */
int const PQ_STARTING_CAPACITY = 50;

/* createPQ
 * input: none
 * output: a pointer to a PriorityQueue (this is malloc-ed so must be freed eventually!)
 *
 * Creates a new empty PriorityQueue and returns a pointer to it.
 */
PriorityQueue *createPQ( ){
    PriorityQueue *ppq = (PriorityQueue *)malloc( sizeof(PriorityQueue) );
    ppq->last = -1;
    ppq->capacity = PQ_STARTING_CAPACITY;
    ppq->data = (pqType *)malloc( sizeof(pqType)*PQ_STARTING_CAPACITY );

    return ppq;
}

/* freePQ
 * input: a pointer to a PriorityQueue
 * output: none
 *
 * frees the given PriorityQueue pointer.  Also possibly call freePQElements if you want to free every element in the PriorityQueue.
 */
void freePQ( PriorityQueue *ppq  ){
    free(ppq->data);
    free(ppq);
}

///* freePQElements
// * input: a pointer to a PriorityQueue
// * output: none
// *
// * Removes and then frees all of the elements currently in the PriorityQueue.  Does not free the PriorityQueue itself.  Call freePQ to also free the PriorityQueue.
// */
//void freeStackElements( PriorityQueue *ppq  ){
//    while( isEmpty(ppq) == false ){
//        free( remove(ppq) );
//    }
//}

/* removePQ
 * input: a pointer to a PriorityQueue
 * output: a pqType
 *
 * removes and returns the pqType stored in the first element in the PriorityQueue.  It does not free the removed element.
 */
pqType removePQ( PriorityQueue *ppq ){
    pqType ret, last;
    int cur, left, right;
    if( isEmptyPQ( ppq ) ){
        /* no element to return */
        printf("ERROR - removePQ - Attempt to retrieve element from an empty list\n");
        exit(-1);
    }
    ret = ppq->data[ 0 ] ; //save return value
    last = ppq->data[ ppq->last ];  //set first element = to last
    ppq->last--;  //remove last element

    cur = 0;
    left = 2*cur + 1;
    right = 2*cur + 2;
    while( right <= ppq->last ){ //Move down heap and check priority of left and right
        if( ppq->data[left].priority <= ppq->data[right].priority && ppq->data[left].priority < last.priority ){
            ppq->data[cur] = ppq->data[left];
            cur = left;
        }
        else if( ppq->data[left].priority > ppq->data[right].priority && ppq->data[right].priority < last.priority ){
            ppq->data[cur] = ppq->data[right];
            cur = right;
        }
        else{
            ppq->data[cur] = last;
            return ret;
        }
        left = 2*cur + 1;
        right = 2*cur + 2;
    }
    if( left <= ppq->last && ppq->data[left].priority < last.priority ){ //Check left element if still in valid range
        ppq->data[cur] = ppq->data[left];
        cur = left;
    }
    ppq->data[cur] = last; //cur is the index last should be stored at
    return ret;
}

/* insertPQ
 * input: a pointer to a stack, a pqType
 * output: none
 *
 * inserts the pqType into the given PriorityQueue.
 */
void insertPQ( PriorityQueue *ppq, pqType pt ){
    //pqType parent;
    int cur, parent;
    if( isFullPQ( ppq ) ){
        /* resize the array */
        ppq->capacity *= 2;
        ppq->data = (pqType*)realloc( ppq->data, ppq->capacity*sizeof(pqType) );
    }
    ppq->last++;
    cur = ppq->last;
    if( cur==0 )
        parent = -1;
    else
        parent = (cur-1)/2;

    while( parent>=0 && ppq->data[parent].priority > pt.priority ){ //Ascend heap until pt's priority is correctly ordered
        ppq->data[cur] = ppq->data[parent];
        cur = parent;
        if( parent == 0 )
            break;
        parent = (cur-1)/2;
    }

    ppq->data[ cur ] = pt;
}

/* promotePQ
 * input: a pointer to a priority queue, a pqType
 * output: none
 *
 * finds the pqType in in the given PriorityQueue and updates the priority value if the new one is lower than existing.
 */
void promotePQ( PriorityQueue *ppq, pqType pt ){
    //pqType parent;
    int cur, parent;

    cur = 0;
    while( cur<=ppq->last && !equals( ppq->data[cur].info, pt.info) ){
        cur++;
    }
    if( cur>ppq->last ){
        /* this data isn't present in the ppq */
        printf("ERROR - promotePQ - Attempt to update element not present in the list\n");
        exit(-1);
    }
    //Update the priority only if it is lower
    if(  ppq->data[ cur ].priority <= pt.priority )
        return;
    ppq->data[ cur ].priority = pt.priority;

    if( cur==0 )
        parent = -1;
    else
        parent = (cur-1)/2;

    while( parent>=0 && ppq->data[parent].priority > pt.priority ){ //Ascend heap until pt's priority is correctly ordered
        ppq->data[cur] = ppq->data[parent];
        cur = parent;
        if( parent == 0 )
            break;
        parent = (cur-1)/2;
    }

    ppq->data[ cur ] = pt;
}

/* getNextPQ
 * input: a pointer to a PriorityQueue
 * output: a pqType
 *
 * returns the pqType on front of the PriorityQueue
 */
pqType getNextPQ( PriorityQueue *ppq ){
    if( isEmptyPQ( ppq ) ){
        /* no element to return */
        printf("ERROR - getNextPQ - Attempt to retrieve element from an empty list\n");
        exit(-1);
    }
    return ppq->data[ 0 ];
}

/* isEmptyPQ
 * input: a pointer to a stack
 * output: a boolean
 *
 * returns TRUE if the stack is empty and FALSE otherwise
 */
bool isEmptyPQ( PriorityQueue *ppq ){
    if( ppq->last == -1 ){
        return true;
    }
    return false;
}

/* isFullPQ
 * input: a pointer to a PriorityQueue
 * output: a boolean
 *
 * returns TRUE if the PriorityQueue is at capacity currently and FALSE otherwise
 * Note that the PriorityQueue handle resizing automatically so you do not need to ever run this as a user of PriorityQueue.
 */
bool isFullPQ( PriorityQueue *ppq ){
    if( ppq->capacity == ppq->last+1 ){
        return true;
    }
    return false;
}
