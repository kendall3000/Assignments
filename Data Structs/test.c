#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "stack.h"
#include "booleanEvaluation.h"
#include "booleanWithError.h"
// Additional method declarations

void freeTokens(char** arrTokens, int tokenCount);
char* unAppend(char* beg, char* end);
char* biAppend(char* beg, char* end, char* mid);
boolean boolNot(boolean bool1);
boolean boolAnd(boolean bool1, boolean bool2);
boolean boolOr(boolean bool1, boolean bool2);
boolean boolNand(boolean bool1, boolean bool2);
boolean boolNor(boolean bool1, boolean bool2);
boolean boolXor(boolean bool1, boolean bool2);
boolean boolCond(boolean bool1, boolean bool2);
boolean boolBicond(boolean bool1, boolean bool2);

/* TODO_done
* printNames
* input: none
* output: none
*
* Prints name of the student who worked on this solution
*/
void printNames( ){
        /* TODO_done : Fill in you and your partner's names (or N/A if you worked individually) */
        printf("This solution was completed by:\n");
        printf("Kendall Ramos\n");
    }
/* TODO
* evaluatePostfix
* input: a postfix expression (calls tokenizeString to get the tokens from the string)
* output: T, F, or E
*
* Uses a stack to evaluates the postfix expression and returns the result as a string where "T" denotes true and "F" denotes false.
* If the postfix expression is invalid it returns "E" to denote an error has occurred. Be sure to use the helpful functions in booleanEvaluation.
*
* Hints:
* - DO NOT free the parameter str. It is freed by the calling function.
* - Be sure to use the helpful functions in booleanEvaluation.
* - Test your code often! Get it working correctly for the first couple test cases instead of trying to solve all of them at once.
*/
char *evaluatePostfix( char *str ){
    /* Your variable Declarations: */
    int tokenCount;
    char** arrTokens = tokenizeString( str, &tokenCount ); /* Currently commented out to prevent a memory leak. Uncomment to get the tokens from str. */
    int i;
    Stack* pfStack = createStack();
    char* popStr = NULL;
    boolean lVal, rVal, pushVal = ERROR;
    /* Your code: */
    for (i=0; i<tokenCount; i++) {
        // push T or F token
        if ( strequals(arrTokens[i], "T") || strequals(arrTokens[i], "F") ) {
        // Push T or F value onto stack
        pushVal = stringToBoolean( arrTokens[i] );
        }
        // unary operators
        else if (strequals(arrTokens[i], "NOT") && !isEmpty(pfStack)) {
            popStr = pop(pfStack);
            lVal = stringToBoolean( popStr );
            // assign not value
            pushVal = boolNot(lVal);
            // free pop'd data
            free(popStr);
        } 
        // binary operators
        else if(pfStack->top >= 1) {
            // get right value and free
            popStr = pop(pfStack);
            rVal = stringToBoolean(popStr);
            free(popStr);
            // get left value and free
            popStr = pop(pfStack);
            lVal = stringToBoolean(popStr);
            free(popStr);
            // calculate new bool value
            if (strequals(arrTokens[i], "AND")) {
                pushVal = boolAnd(lVal, rVal);
            }else if (strequals(arrTokens[i], "NAND")) {
                pushVal = boolNand(lVal, rVal);
            } else if (strequals(arrTokens[i], "OR")) {
                pushVal = boolOr(lVal, rVal);
            } else if (strequals(arrTokens[i], "NOR")) {
                pushVal = boolNor(lVal, rVal);
            }else if (strequals(arrTokens[i], "XOR")) {
                pushVal = boolXor(lVal, rVal);
            } else if (strequals(arrTokens[i], "COND")) {
                pushVal = boolCond(lVal, rVal);
            } else { 
                pushVal = boolBicond(lVal, rVal);
            }
        } else {
                // Not enough elements in array, return ERROR
                freeStackElements(pfStack);
                freeStack(pfStack);
                freeTokens(arrTokens, tokenCount);
                // return ERROR
                return booleanToString( ERROR );
            }
        // Push final value onto stack
        push(pfStack, booleanToString( pushVal ));
    }
    // Free remaining items
    popStr = pop(pfStack);
    if ( (popStr == NULL) || (pfStack->top > -1) ) {
        // free held element in poStr
        free(popStr);
        // Return error
        popStr = booleanToString( ERROR );
    }
    // Free stack and arrToken array
    freeStackElements(pfStack);
    freeStack(pfStack);
    freeTokens(arrTokens, tokenCount);
    // Return last value
    return popStr; 
}
/* TODO
* postfixToInfix
* input: a postfix expression (calls tokenizeString to get the tokens from the string)
* output: the equivalent infix expression
*
* Uses a stack to convert str to its equivalent expression in infix.
* You can assume that the postfix expression is valid
*
* Hints:
* - DO NOT free the parameter str. It is freed by the calling function.
* - Be sure to use the helpful functions in booleanEvaluation.
* - Test your code often! Get it working correctly for the first couple test cases instead of trying to solve all of them at once.
*/
char *postfixToInfix( char *str ){
    int tokenCount;
    char** arrTokens = tokenizeString( str, &tokenCount ); 
    int i;
    // Placeholder strings for pop values
    char* lVal = NULL;
    char* rVal = NULL;
    char* pushVal = NULL;
    // Create stack to hold tokens
    Stack* pfStack = createStack();
    for (i=0; i<tokenCount; i++) {
        // push boolean
        if ( strequals(arrTokens[i], "T") || strequals(arrTokens[i], "F")) {
            // malloc since pushing char* to stack 
            char* pushBool = (char*) malloc(sizeof(char) * 2);
            // Copy to prevent overwrite
            strcpy(pushBool, arrTokens[i]);
            push(pfStack, pushBool);
        }else {
            rVal = pop(pfStack);
            if (strequals(arrTokens[i], "NOT")) {
                // Unary operator
                pushVal = unAppend("NOT", rVal);
                // Free right after use
                free(rVal);
            } else {
                // grab left value
                lVal = pop(pfStack);
                // binary operator
                pushVal = biAppend(lVal, arrTokens[i], rVal);
                // Free right after use
                free(rVal);
                free(lVal);
            }
            // Push final value onto
            push(pfStack, pushVal);
        }
    }
    // save value to not be deleted when freeing stack
    pushVal = pop(pfStack);
    // Free items
    freeStackElements(pfStack);
    freeStack(pfStack);
    freeTokens(arrTokens, tokenCount);
    // return final value
    return pushVal; /* Replace this with your actual solution to return */
}

/* You may want to create some helper functions down here! */
void freeTokens(char** arrTokens, int tokenCount) {
    // Free token array
    int i;
    for (i=0; i<tokenCount; i++) {
        // free individual tokens
        free(arrTokens[i]);
    }
    // free array of tokens
    free(arrTokens);
}

char* unAppend(char* beg, char* end) {
    // Lengths of each string
    int bLen = strlen(beg);
    int eLen = strlen(end);
    // Length of spaces and () needed, for easier math
    int base = strlen("(___)");
    size_t length = bLen + eLen + base; 
    // strlen(beg) + strlen(end) + strlen("(___)");
    char* result = (char*)malloc(sizeof(char) * (length) + 1);
    // printf string onto string, easier than strcat and less buddy
    snprintf(result, length+1, "( %s %s )", beg, end);
    // return concat string
    return result;
    }
char* biAppend(char* beg, char* mid, char* end) {// Lengths of each string
int bLen = strlen(beg);
int mLen = strlen(mid);
int eLen = strlen(end);
// Length of spaces and () needed, for easier math
int base = strlen("(____)");

size_t length = bLen + mLen + eLen + base; //strlen(beg) + strlen(mid) + strlen(end) + strlen("(____)");
char* result = (char*)malloc(sizeof(char) * length + 1);
// printf string onto string, easier than strcat and less buddy
snprintf(result, length+1, "( %s %s %s )", beg, mid, end);
// return concat string
return result;

}
// All boolOp functions are premade boolean operation functions to modularize logic
// due to boolean values actually being enums
boolean boolNot(boolean bool1) {
    switch(bool1) {
        case TRUE:
        return FALSE;
        break;
        case FALSE:
        return TRUE;
        break;
        default:
        return ERROR;
        }
        }
boolean boolAnd(boolean bool1, boolean bool2) {
    if (bool1 == TRUE && bool2 == TRUE) {
        return TRUE;
        } else {
            return FALSE;
            }
            }
boolean boolOr(boolean bool1, boolean bool2) {
    if (bool1 == TRUE || bool2 == TRUE) {
        return TRUE;
        } else {
            return FALSE;
            }
            }
boolean boolNand(boolean bool1, boolean bool2) {
    return boolNot(boolAnd(bool1, bool2));
    }
boolean boolNor(boolean bool1, boolean bool2) {
    return boolNot(boolOr(bool1, bool2));
    }
boolean boolXor(boolean bool1, boolean bool2) {
    return (bool1 == TRUE) ^ (bool2 == TRUE);
    }
boolean boolCond(boolean bool1, boolean bool2) {
    return (boolNot(bool1) == TRUE) || (bool2 == TRUE);
    }
boolean boolBicond(boolean bool1, boolean bool2) {
    return bool1 == bool2;
    }