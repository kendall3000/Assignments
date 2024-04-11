#include "stack.h"

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
    ps->data = (char **)malloc( sizeof(char *)*STACK_STARTING_CAPACITY );

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

/* freeStackElements
 * input: a pointer to a stack
 * output: none
 *
 * pops and then frees all of the elements currently in the stack.  Does not free the stack itself.  Call freeStack to also free the stack.
 */
void freeStackElements( Stack *ps  ){
    while( isEmpty(ps) == FALSE ){
        free( pop(ps) );
    }
}

/* pop
 * input: a pointer to a stack
 * output: a string
 *
 * pops and returns the char* stored in the top element in the stack.  It does not free the pop-ed element.
 */
char *pop( Stack *ps ){
    if( isEmpty( ps ) ){
        /* no element to return */
        return NULL;
    }
    return ps->data[ ps->top-- ];
}

/* push
 * input: a pointer to a stack, a string
 * output: none
 *
 * pushes the string onto the top of the given stack.
 */
void push( Stack *ps, char *str ){
    if( isFull( ps ) ){
        /* resize the array */
        ps->capacity *= 2;
        ps->data = (char **)realloc( ps->data, ps->capacity*sizeof(char *) );
    }
    ps->data[ ++ps->top ] = str;
}

/* top
 * input: a pointer to a stack
 * output: a string
 *
 * returns the string on top of the stack
 */
char *top( Stack *ps ){
    if( isEmpty( ps ) ){
        /* no element to return */
        return NULL;
    }
    return ps->data[ ps->top ];
}

/* isEmpty
 * input: a pointer to a stack
 * output: a boolean
 *
 * returns TRUE if the stack is empty and FALSE otherwise
 */
boolean isEmpty( Stack *ps ){
    if( ps->top == -1 ){
        return TRUE;
    }
    return FALSE;
}

/* isFull
 * input: a pointer to a stack
 * output: a boolean
 *
 * returns TRUE if the stack is at capacity currently and FALSE otherwise
 * Note that the stack handle resizing automatically so you do not need to ever run this as a user of stack.
 */
boolean isFull( Stack *ps ){
    if( ps->capacity == ps->top+1 ){
        return TRUE;
    }
    return FALSE;
}