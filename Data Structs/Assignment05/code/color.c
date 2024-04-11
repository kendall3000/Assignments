#include "color.h"

/************************ COLOR PRINTING FUNCTIONS ************************/

void red( bool enabled ){
    if( enabled )
        printf("\033[0;31m");
}

void green( bool enabled ){
    if( enabled )
        printf("\033[0;32m");
}

void yellow( bool enabled ){
    if( enabled )
        printf("\033[0;33m");
}

void reset( bool enabled ){
    if( enabled )
        printf("\033[0m");
}
