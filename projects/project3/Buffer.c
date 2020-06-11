#include <sys/time.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "Buffer.h"

/* --------------- Buffer Constructor/Destructor -------------- */
void initializeBuffer(Buffer** Buffer){

    // allocate memory for number of Entry Pointers...
    (*Buffer)->entries = (Entry**) malloc(BUFFERSIZE * sizeof(Entry*));
    for(int i = 0; i < BUFFERSIZE; i++){
        (*Buffer)->entries[i] = (Entry*) malloc(sizeof(Entry));
    }

    for(int i = 0; i < BUFFERSIZE; i++){

        //... and initialize each one
        initializeEntry(&((*Buffer)->entries[i]));
    }

    // set the rest of the Buffer's attributes to default values
    (*Buffer)->count = 0;
    (*Buffer)->head = 0;
    (*Buffer)->tail = 0;
    (*Buffer)->size = 0;

}

void destroyBuffer(Buffer** Buffer){

    // destroy each Entry Pointer...
    for(int i = 0; i < BUFFERSIZE; i++){
        destroyEntry(&((*Buffer)->entries[i]));
    }
    // ...and the list of Entries itself
    free((*Buffer)->entries);

    // finally, free self
    free((*Buffer));

}
/* ----------------------------------------------------------- */


/* -------------- Buffer Getters and Setters ----------------- */

/* ----------------------------------------------------------- */