#include <sys/time.h>
#include <string.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include "Buffer.h"

//sem_t mutex;

/* --------------- Buffer Constructor/Destructor -------------- */
void initializeBuffer(Buffer** Buffer){
    // set the rest of the Buffer's attributes to default values
    (*Buffer)->entryCount = 0;
    (*Buffer)->head = 0;
    (*Buffer)->tail = 0;
    (*Buffer)->highestEntryNum = 0;
    (*Buffer)->isFull = false;

}
Buffer* constructBuffer(){
    
    Buffer* retBuffer = (Buffer*) malloc(sizeof(Buffer));

    // allocate memory for number of Entry Pointers...
    retBuffer->entries = (Entry**) malloc(MAXENTRIES * sizeof(Entry*));
    // Next create each Entry in the Buffer
    for(int i = 0; i < MAXENTRIES; i++){
        retBuffer->entries[i] = constructEntry();
    }

    //Finally set Buffer's default values
    initializeBuffer(&retBuffer);

    // return Buffer
    return retBuffer;
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

    int buffSize = MAXENTRIES;

    // If the buffer is full, the capacity is at its max
    if(!(*Buffer)->isFull){


        // Otherwise, if head is >= to tail, we subtract to get size
        if((*Buffer)->head >= (*Buffer)->tail){
            
            buffSize = ((*Buffer)->head - (*Buffer)->tail);
        
        // If the tail is > than head, we need to add by the capaicty to get size
        } else {

            buffSize = (MAXENTRIES + (*Buffer)->head - (*Buffer)->tail);
        }
    }

    return buffSize;
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

void incrementBufferhighestEntryNum(Buffer** Buffer){
    /* 
        Method which increments a Buffer's inserted count.
    */
    (*Buffer)->highestEntryNum ++;
}

void incrementHeadPointer(Buffer** Buffer){

    int head = getBufferHeadIndex(Buffer);
    int tail = getBufferTailIndex(Buffer);


    // If the buffer is full we use modulo to set head and tail to 0
    if((*Buffer)->isFull){

        setBufferTailIndex(Buffer, (tail + 1) % MAXENTRIES);
    
    //In the case of the buffer being full, this will assure that head and tail both equal 0
    }

    setBufferHeadIndex(Buffer, (head+1) % MAXENTRIES);

    // Next, set Buffer's inFull boolean appropriately
    // Will go true if the Buffer's head and tail are the same.
    // However when initializing, the default value is false, so I will be able
    // Put values in
    (*Buffer)->isFull = (getBufferHeadIndex(Buffer) == getBufferTailIndex(Buffer));
}

void incrementTailPointer(Buffer** Buffer){

    // First we advance the tail pointer by one...
    (*Buffer)->tail = (getBufferTailIndex(Buffer) + 1) % MAXENTRIES;

    // Then we say that the Buffer isn't full
    (*Buffer)->isFull = false;

}

/* ----------------------------------------------------------- */

/* --------------------- Enqueue/Dequeue --------------------- */

int enqueue(Buffer** Buffer, Entry** Entry){

    // wait
    //sem_wait(&mutex);
    //fprintf(stdout, "enqueing...\n");

    /* ------------  Critical Section ------------- */
    //sleep(4);

    // Check if Buffer is full
    if(isFull(Buffer)){

        fprintf(stderr, "Error, unable to equeue Entry: %i\n", getEntryNum(Entry));
        // signal
        //fprintf(stdout, "stopped enqueing...\n");
        //sem_post(&mutex);
        return -1;

    }


    /* --------- Prep Entry to be enqued ----------*/
    // Increment inserted Count and assign said value to Entry
    incrementBufferhighestEntryNum(Buffer);
    setEntryNum(Entry, (*Buffer)->highestEntryNum);

    // Assign current time to Entry
    gettimeofday(&(*Entry)->timeStamp, NULL);
    /* ---------------------------------------------*/

    /* --- Store Entry in address indicated by head --- */

    //destroy entry in current spot to make way for new
    destroyEntry(&(*Buffer)->entries[getBufferHeadIndex(Buffer)]);
    // push Entry to Buffer
    (*Buffer)->entries[getBufferHeadIndex(Buffer)] = *Entry;

    //Increment head
    incrementHeadPointer(Buffer);
    /* ------------------------------------------------ */
        
    /* -------------------------------------------- */

    // signal
    //fprintf(stdout, "stopped enqueing...\n");
    //sem_post(&mutex);
    return 1;

}

int dequeue(Buffer** Buffer){

    if(isEmpty(Buffer)){
        fprintf(stderr, "Error! Unable to dequeue Entry. Buffer is empty.\n\n");
        return -1;
    }

    // Reinitialize entry and increment tail pointer
    Entry* Entry = (*Buffer)->entries[getBufferTailIndex(Buffer)];
    initializeEntry(&Entry);
    incrementTailPointer(Buffer);
    return 1;

}
/* ----------------------------------------------------------- */

/* --------------------- Buffer Helpers ---------------------- */

void printLimitedBufferStatus(Buffer** Buffer){

    fprintf(stdout, "Entry Count: %i\n", getBufferEntryCount(Buffer));
    fprintf(stdout, "Head Index: %i\n", getBufferHeadIndex(Buffer));
    fprintf(stdout, "Tail Index: %i\n", getBufferTailIndex(Buffer));
    fprintf(stdout, "Entry Count: %i\n", getBufferEntryCount(Buffer));

}

void printFullBufferStatus(Buffer** Buffer){
    printLimitedBufferStatus(Buffer);
    fprintf(stdout, "-------------------------------------------------\n");
    for(int i = 0; i < MAXENTRIES; i++){
        printEntryStatus(&(*Buffer)->entries[i]);
    }
    
}

bool isFull(Buffer** Buffer){
    return((*Buffer)->isFull);
}

bool isEmpty(Buffer** Buffer){
    //If the head and tail both equal,then the Buffer is empty
    return(!(*Buffer)->isFull && ((*Buffer)->head == (*Buffer)->tail));
}

/* ----------------------------------------------------------- */
