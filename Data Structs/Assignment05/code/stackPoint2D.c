#include "stackPoint2D.h"

/*
 * Default starting size for the stack
 */
int const STACK_STARTING_CAPACITY = 50;

/* createStack
 * input: none
 * output: a pointer to a stack (this is malloc-ed so must be freed eventually!)
 *
 * Creates a new empty stack and returns a pointer to it.
 */
Stack *createStack( ){
    Stack *ps = (Stack *)malloc( sizeof(Stack) );
    ps->top = -1;
    ps->capacity = STACK_STARTING_CAPACITY;
    ps->data = (stackType *)malloc( sizeof(char *)*STACK_STARTING_CAPACITY );

    return ps;
}

/* freeStack
 * input: a pointer to a stack
 * output: none
 *
 * frees the given stack pointer.  Also call freeStackElements if you want to free every element in the stack.
 */
void freeStack( Stack *ps  ){
    free(ps->data);
    free(ps);
}

///* freeStackElements
// * input: a pointer to a stack
// * output: none
// *
// * pops and then frees all of the elements currently in the stack.  Does not free the stack itself.  Call freeStack to also free the stack.
// */
//void freeStackElements( Stack *ps  ){
//    while( isEmpty(ps) == false ){
//        free( pop(ps) );
//    }
//}

/* pop
 * input: a pointer to a stack
 * output: a stackType
 *
 * pops and returns the char* stored in the top element in the stack.  It does not free the pop-ed element.
 */
stackType pop( Stack *ps ){
    if( isEmptyStack( ps ) ){
        /* no element to return */
        printf("ERROR - pop - Attempt to retrieve element from an empty stack\n");
        exit(-1);
    }
    return ps->data[ ps->top-- ];
}

/* push
 * input: a pointer to a stack, a stackType
 * output: none
 *
 * pushes the stackType onto the top of the given stack.
 */
void push( Stack *ps, stackType st ){
    if( isFullStack( ps ) ){
        /* resize the array */
        ps->capacity *= 2;
        ps->data = (stackType *)realloc( ps->data, ps->capacity*sizeof(stackType) );
    }
    ps->data[ ++ps->top ] = st;
}

/* top
 * input: a pointer to a stack
 * output: a stackType
 *
 * returns the stackType on top of the stack
 */
stackType top( Stack *ps ){
    if( isEmptyStack( ps ) ){
        /* no element to return */
        printf("ERROR - top - Attempt to retrieve element from an empty stack\n");
        exit(-1);
    }
    return ps->data[ ps->top ];
}

/* isEmpty
 * input: a pointer to a stack
 * output: a boolean
 *
 * returns TRUE if the stack is empty and FALSE otherwise
 */
bool isEmptyStack( Stack *ps ){
    if( ps->top == -1 ){
        return true;
    }
    return false;
}

/* isFull
 * input: a pointer to a stack
 * output: a boolean
 *
 * returns TRUE if the stack is at capacity currently and FALSE otherwise
 * Note that the stack handle resizing automatically so you do not need to ever run this as a user of stack.
 */
bool isFullStack( Stack *ps ){
    if( ps->capacity == ps->top+1 ){
        return true;
    }
    return false;
}
