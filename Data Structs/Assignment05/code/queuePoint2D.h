#ifndef _Point2D_h
#define _Point2D_h
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "point2D.h"

typedef Point2D queueType; //Change this line to set the type for the queue to store

typedef struct LLNode
{
    queueType qt;             //queueType contained in this node
    struct LLNode *pNext;       //pointer to the next node in the linked list
}  LLNode;

typedef struct Queue
{
    LLNode *qFront;             //pointer to the first element of the queue
    LLNode *qRear;              //pointer to the last element of the queue
} Queue;

Queue *createQueue( );
void freeQueue( Queue *pq );

queueType getNextQueue( Queue *pq );
queueType dequeue( Queue *pq );
void enqueue( Queue *pq, queueType qt );

bool isEmptyQueue( Queue *pq );

#endif
