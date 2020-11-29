#include <sys/time.h>
#include <string.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include "TopicQueue.h"

//sem_t mutex;

/* --------------- TopicQueue Constructor/Destructor -------------- */
void initializeTopicQueue(TopicQueue** TopicQueue){
    // set the rest of the TopicQueue's attributes to default values
    (*TopicQueue)->entryCount = 0;
    (*TopicQueue)->head = 0;
    (*TopicQueue)->tail = 0;
    (*TopicQueue)->highestEntryNum = 0;
    (*TopicQueue)->isFull = false;

}
TopicQueue* constructTopicQueue(){
    
    TopicQueue* retTopicQueue = (TopicQueue*) malloc(sizeof(TopicQueue));

    // allocate memory for number of Entry Pointers...
    retTopicQueue->entries = (Entry**) malloc(MAXENTRIES * sizeof(Entry*));
    // Next create each Entry in the TopicQueue
    for(int i = 0; i < MAXENTRIES; i++){
        retTopicQueue->entries[i] = constructEntry();
    }

    //Finally set TopicQueue's default values
    initializeTopicQueue(&retTopicQueue);

    // return TopicQueue
    return retTopicQueue;
}

void destroyTopicQueue(TopicQueue** TopicQueue){

    // destroy each Entry Pointer...
    for(int i = 0; i < MAXENTRIES; i++){
        destroyEntry(&((*TopicQueue)->entries[i]));
    }
    // ...and the list of Entries itself
    free((*TopicQueue)->entries);

    // finally, free self
    free((*TopicQueue));

}
/* ----------------------------------------------------------- */


/* -------------- TopicQueue Getters and Setters ----------------- */

int getTopicQueueEntryCount(TopicQueue** TopicQueue){
    return((*TopicQueue)->entryCount);
}
int getTopicQueueHeadIndex(TopicQueue** TopicQueue){
    return((*TopicQueue)->head);
}
int getTopicQueueTailIndex(TopicQueue** TopicQueue){
    return((*TopicQueue)->tail);
}

int getTopicQueueSize(TopicQueue** TopicQueue){

    int buffSize = MAXENTRIES;

    // If the TopicQueue is full, the capacity is at its max
    if(!(*TopicQueue)->isFull){


        // Otherwise, if head is >= to tail, we subtract to get size
        if((*TopicQueue)->head >= (*TopicQueue)->tail){
            
            buffSize = ((*TopicQueue)->head - (*TopicQueue)->tail);
        
        // If the tail is > than head, we need to add by the capaicty to get size
        } else {

            buffSize = (MAXENTRIES + (*TopicQueue)->head - (*TopicQueue)->tail);
        }
    }

    return buffSize;
}

int incrementTopicQueueEntryCount(TopicQueue** TopicQueue){
    /*
        Method which increments a TopicQueue's entry count.
        returns -1 if it encountered an error and prints
        error message. returns 1 otherwise
    */
    
    // Make sure that EntryCount isn't = to MAXENTRIES
    if((*TopicQueue)->entryCount == MAXENTRIES){
        fprintf(stderr, "Error! Unable to increment Entry count, TopicQueue at maximum capacity.\n");
        return -1;
    
    } else {
        (*TopicQueue)->entryCount = (*TopicQueue)->entryCount + 1;
        return 1;
    }
}
int decrementTopicQueueEntryCount(TopicQueue** TopicQueue){
    /*
        Method which decrements a TopicQueue's entry count.
        returns -1 if it encountered an error and prints
        error message
    */

    // Make sure that EntryCount isn't == 0
    if((*TopicQueue)->entryCount == 0){
        fprintf(stderr, "Error! Unable to decrement Entry count, TopicQueue is empty.\n");
        return -1;
    
    } else {
        (*TopicQueue)->entryCount = (*TopicQueue)->entryCount - 1;
        return 1;
    }
}
void setTopicQueueHeadIndex(TopicQueue** TopicQueue, int head){
    /*
        Method which sets a TopicQueue's head index.
    */
    (*TopicQueue)->head = head;
}

void setTopicQueueTailIndex(TopicQueue** TopicQueue, int tail){
    /* 
        Method which sets a TopicQueue's tail index.
    */
    (*TopicQueue)->tail = tail;
}

void incrementTopicQueuehighestEntryNum(TopicQueue** TopicQueue){
    /* 
        Method which increments a TopicQueue's inserted count.
    */
    (*TopicQueue)->highestEntryNum ++;
}

void incrementHeadPointer(TopicQueue** TopicQueue){

    int head = getTopicQueueHeadIndex(TopicQueue);
    int tail = getTopicQueueTailIndex(TopicQueue);


    // If the TopicQueue is full we use modulo to set head and tail to 0
    if((*TopicQueue)->isFull){

        setTopicQueueTailIndex(TopicQueue, (tail + 1) % MAXENTRIES);
    
    //In the case of the TopicQueue being full, this will assure that head and tail both equal 0
    }

    setTopicQueueHeadIndex(TopicQueue, (head+1) % MAXENTRIES);

    // Next, set TopicQueue's inFull boolean appropriately
    // Will go true if the TopicQueue's head and tail are the same.
    // However when initializing, the default value is false, so I will be able
    // Put values in
    (*TopicQueue)->isFull = (getTopicQueueHeadIndex(TopicQueue) == getTopicQueueTailIndex(TopicQueue));
}

void incrementTailPointer(TopicQueue** TopicQueue){

    // First we advance the tail pointer by one...
    (*TopicQueue)->tail = (getTopicQueueTailIndex(TopicQueue) + 1) % MAXENTRIES;

    // Then we say that the TopicQueue isn't full
    (*TopicQueue)->isFull = false;

}

/* ----------------------------------------------------------- */

/* --------------------- Enqueue/Dequeue --------------------- */

int enqueue(TopicQueue** TopicQueue, Entry** Entry){

    // wait
    //sem_wait(&mutex);
    //fprintf(stdout, "enqueing...\n");

    /* ------------  Critical Section ------------- */
    //sleep(4);

    /*
    // Check if TopicQueue is full
    if(isFull(TopicQueue)){

        fprintf(stderr, "Error, unable to enqueue Entry: %i, TopicQueue full\n", getEntryNum(Entry));

        return -1;

    }
    */


    /* --------- Prep Entry to be enqued ----------*/
    // Increment inserted Count and assign said value to Entry
    incrementTopicQueuehighestEntryNum(TopicQueue);
    setEntryNum(Entry, (*TopicQueue)->highestEntryNum);

    // Assign current time to Entry
    gettimeofday(&(*Entry)->timeStamp, NULL);
    /* ---------------------------------------------*/

    /* --- Store Entry in address indicated by head --- */

    //destroy entry in current spot to make way for new
    destroyEntry(&(*TopicQueue)->entries[getTopicQueueHeadIndex(TopicQueue)]);
    // push Entry to TopicQueue
    (*TopicQueue)->entries[getTopicQueueHeadIndex(TopicQueue)] = *Entry;

    //Increment head
    incrementHeadPointer(TopicQueue);
    /* ------------------------------------------------ */
        
    /* -------------------------------------------- */

    // signal
    //fprintf(stdout, "stopped enqueing...\n");
    //sem_post(&mutex);
    return 1;

}

int dequeue(TopicQueue** TopicQueue){

    if(isEmpty(TopicQueue)){
        fprintf(stderr, "Error! Unable to dequeue Entry. TopicQueue is empty.\n\n");
        return -1;
    }

    // Reinitialize entry and increment tail pointer
    Entry* Entry = (*TopicQueue)->entries[getTopicQueueTailIndex(TopicQueue)];
    initializeEntry(&Entry);
    incrementTailPointer(TopicQueue);
    return 1;

}
/* ----------------------------------------------------------- */

/* --------------------- TopicQueue Helpers ---------------------- */

void printLimitedTopicQueueStatus(TopicQueue** TopicQueue){

    fprintf(stdout, "Entry Count: %i\n", getTopicQueueEntryCount(TopicQueue));
    fprintf(stdout, "Head Index: %i\n", getTopicQueueHeadIndex(TopicQueue));
    fprintf(stdout, "Tail Index: %i\n", getTopicQueueTailIndex(TopicQueue));
    fprintf(stdout, "Entry Count: %i\n", getTopicQueueEntryCount(TopicQueue));

}

void printFullTopicQueueStatus(TopicQueue** TopicQueue){
    printLimitedTopicQueueStatus(TopicQueue);
    fprintf(stdout, "-------------------------------------------------\n");
    for(int i = 0; i < MAXENTRIES; i++){
        printEntryStatus(&(*TopicQueue)->entries[i]);
    }
    
}

bool isFull(TopicQueue** TopicQueue){
    return((*TopicQueue)->isFull);
}

bool isEmpty(TopicQueue** TopicQueue){
    //If the head and tail both equal,then the TopicQueue is empty
    return(!(*TopicQueue)->isFull && ((*TopicQueue)->head == (*TopicQueue)->tail));
}

/* ----------------------------------------------------------- */
