#include <sys/time.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "Buffer.h"

/* --------------- Buffer Constructor/Destructor -------------- */
void initializeBuffer(Buffer** Buffer){

    // allocate memory for number of Entry Pointers...
    (*Buffer)->entries = (Entry**) malloc(MAXENTRIES * sizeof(Entry*));
    for(int i = 0; i < MAXENTRIES; i++){
        (*Buffer)->entries[i] = (Entry*) malloc(sizeof(Entry));
    }

    for(int i = 0; i < MAXENTRIES; i++){

        //... and initialize each one
        initializeEntry(&((*Buffer)->entries[i]));
    }

    // set the rest of the Buffer's attributes to default values
    (*Buffer)->entryCount = 0;
    (*Buffer)->head = 0;
    (*Buffer)->tail = 0;
    (*Buffer)->insertedCount = 0;

}

void destroyBuffer(Buffer** Buffer){

    // destroy each Entry Pointer...
    for(int i = 0; i < MAXENTRIES; i++){
        destroyEntry(&((*Buffer)->entries[i]));
    }
    // ...and the list of Entries itself
    free((*Buffer)->entries);

    // finally, free self
    free((*Buffer));

}
/* ----------------------------------------------------------- */


/* -------------- Buffer Getters and Setters ----------------- */

int getBufferEntryCount(Buffer** Buffer){
    return((*Buffer)->entryCount);
}
int getBufferHeadIndex(Buffer** Buffer){
    return((*Buffer)->head);
}
int getBufferTailIndex(Buffer** Buffer){
    return((*Buffer)->tail);
}
int getBufferSize(Buffer** Buffer){
    return((*Buffer)->insertedCount);
}

int incrementBufferEntryCount(Buffer** Buffer){
    /*
        Method which increments a Buffer's entry count.
        returns -1 if it encountered an error and prints
        error message. returns 1 otherwise
    */
    
    // Make sure that EntryCount isn't = to MAXENTRIES
    if((*Buffer)->entryCount == MAXENTRIES){
        fprintf(stderr, "Error! Unable to increment Entry count, Buffer at maximum capacity.\n");
        return -1;
    
    } else {
        (*Buffer)->entryCount = (*Buffer)->entryCount + 1;
        return 1;
    }
}
int decrementBufferEntryCount(Buffer** Buffer){
    /*
        Method which decrements a Buffer's entry count.
        returns -1 if it encountered an error and prints
        error message
    */

    // Make sure that EntryCount isn't == 0
    if((*Buffer)->entryCount == 0){
        fprintf(stderr, "Error! Unable to decrement Entry count, Buffer is empty.\n");
        return -1;
    
    } else {
        (*Buffer)->entryCount = (*Buffer)->entryCount - 1;
        return 1;
    }
}
void setBufferHeadIndex(Buffer** Buffer, int head){
    /*
        Method which sets a Buffer's head index.
    */
    (*Buffer)->head = head;
}

void setBufferTailIndex(Buffer** Buffer, int tail){
    /* 
        Method which sets a Buffer's tail index.
    */
    (*Buffer)->tail = tail;
}

void incrementBufferInsertedCount(Buffer** Buffer){
    /* 
        Method which increments a Buffer's inserted count.
    */
    (*Buffer)->insertedCount ++;
}

/* ----------------------------------------------------------- */

/* --------------------- Buffer Helpers ---------------------- */

void printBufferStatus(Buffer** Buffer){

    fprintf(stdout, "Entry Count: %i\n", getBufferEntryCount(Buffer));
    fprintf(stdout, "Head Index: %i\n", getBufferHeadIndex(Buffer));
    fprintf(stdout, "Tail Index: %i\n", getBufferTailIndex(Buffer));
    fprintf(stdout, "Entry Count: %i\n", getBufferEntryCount(Buffer));

}

/* ----------------------------------------------------------- */
