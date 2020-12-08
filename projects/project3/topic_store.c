#include <sys/time.h>
#include <string.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include "topic_store.h"

//sem_t mutex;

/* --------------- Entry Constructor/Destructor --------------- */
void initializeEntry(Entry** Entry){

    // get execution time
    struct timeval executionTime = (struct timeval){0};
    //gettimeofday(&executionTime, NULL);

    char* photoURL_EMPTY = "NULL";
    char* photoCaption_EMPTY = "NULL";

    // set Entry's attributes to defaults
    setEntryNum(Entry, -1);
    setEntryTimeStamp(Entry, &executionTime);
    setEntryPubID(Entry, -1);
    setEntryPhotoURL(Entry, &photoURL_EMPTY);
    setEntryPhotoCaption(Entry, &photoCaption_EMPTY);
}

Entry* constructEntry(){

    Entry* retEntry = (Entry*) malloc(sizeof(Entry));

    retEntry->photoURL = (char*) malloc(URLSIZE + 1 * sizeof(char));
    retEntry->photoCaption = (char*) malloc(CAPSIZE + 1 * sizeof(char));

    initializeEntry(&retEntry);

    return retEntry;
}

void destroyEntry(Entry** Entry){

    // deallocate memory for URL and Caption
    free((*Entry)->photoURL);
    free((*Entry)->photoCaption);

    // finally, destroy self
    free((*Entry));

}

/* ------------------------------------------------------------ */

/* --------------- Entry Setters --------------- */
void setEntryTimeStamp(Entry** Entry, struct timeval* newTimeStamp){

    memcpy(&(*Entry)->timeStamp, newTimeStamp, sizeof(*newTimeStamp));
}

void setEntryNum(Entry** Entry, int newEntryNum){
    (*Entry)->entryNum = newEntryNum;
}

void setEntryPubID(Entry** Entry, int newPubID){
    (*Entry)->pubID = newPubID;
}

void setEntryPhotoURL(Entry** Entry, char** newPhotoURL){
    if(newPhotoURL == NULL){
        (*Entry)->photoURL = NULL;
    
    } else {
        strcpy((*Entry)->photoURL, *newPhotoURL);
    }
}

void setEntryPhotoCaption(Entry** Entry, char** newPhotoCaption){
    if(newPhotoCaption == NULL){
        (*Entry)->photoCaption = NULL;
    
    } else {
        strcpy((*Entry)->photoCaption, *newPhotoCaption);
    }
}
/* -------------------------------------------------- */


/* --------------- Entry Getters --------------- */
struct timeval getEntryTimeStamp(Entry** Entry){
    return (*Entry)->timeStamp;
}

int getEntryNum(Entry** Entry){
    return (*Entry)->entryNum;
}

int getEntryPubID(Entry** Entry){
    return (*Entry)->pubID;
}

char* getEntryPhotoURL(Entry** Entry){
    return (*Entry)->photoURL;
}

char* getEntryPhotoCaption(Entry** Entry){
    return (*Entry)->photoCaption;
}
/* -------------------------------------------------- */

/* --------------- Entry Helpers --------------- */
void printEntryStatus(Entry** Entry){

    // Print Entry time stamp in seconds.milliseconds
    fprintf(stdout, "Time: %li.%li s\n", getEntryTimeStamp(Entry).tv_sec, getEntryTimeStamp(Entry).tv_usec);
    fprintf(stdout, "Entry Num: %i\n", getEntryNum(Entry));
    fprintf(stdout, "Entry PubID: %i\n", getEntryPubID(Entry));
    fprintf(stdout, "Entry Photo URL: %s\n", getEntryPhotoURL(Entry));
    fprintf(stdout, "Entry Caption: %s\n", getEntryPhotoCaption(Entry));
    fprintf(stdout, "\n");
}
/* -------------------------------------------------- */

/* --------------- TopicQueue Constructor/Destructor -------------- */
void initializeTopicQueue(TopicQueue** TopicQueue){
    // set the rest of the TopicQueue's attributes to default values
    (*TopicQueue)->entryCount = 0;
    (*TopicQueue)->head = 0;
    (*TopicQueue)->tail = 0;
    (*TopicQueue)->highestEntryNum = 0;
    (*TopicQueue)->isFull = false;

}
TopicQueue* constructTopicQueue(int id, char* topicName, int size){
    
    // Allocate mem for new topic Queue
    TopicQueue* retTopicQueue = (TopicQueue*) malloc(sizeof(TopicQueue));

    // allocate memory for number of Entry Pointers...
    retTopicQueue->entries = (Entry**) malloc(MAXENTRIES * sizeof(Entry*));
    // Next create each Entry in the TopicQueue
    for(int i = 0; i < MAXENTRIES; i++){
        retTopicQueue->entries[i] = constructEntry();
    }

    // Copy over new name
    strcpy(retTopicQueue->name, topicName);
    // Set desired TopicQueue length (this is usually MAXENTRIES)
    retTopicQueue->size = size;

    //set TopicQueue to start empty
    initializeTopicQueue(&retTopicQueue);
    retTopicQueue->entryCount = 1;
    retTopicQueue->head = -1;
    retTopicQueue->tail = 0;

    // Set up mutex
    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
    pthread_mutexattr_setrobust(&attr, PTHREAD_MUTEX_ROBUST);
    pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_ERRORCHECK);
    pthread_mutex_init(&(retTopicQueue->lock), &attr);
    pthread_mutexattr_destroy(&attr);

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

    // destroy mutex
    pthread_mutex_destroy(&(*TopicQueue)->lock);

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
    int isFull = 0;
    int returnVal = 1;
    
    // Lock the queue
    pthread_mutex_lock(&(*TopicQueue)->lock);
    /* ------------  Critical Section ------------- */
    //sleep(4);

    // Store head/tail indexes for future reference
    int head = (*TopicQueue)->head;
    int tail = (*TopicQueue)->tail;

    // If TopicQueue is empty, we need to set head/tail values to 0
    if(head == -1){
        (*TopicQueue)->head = 0;
        (*TopicQueue)->tail = 0;
    
    // If the TopicQueue isn't empty, but isn't full, we can simply increment the tail
    } else if((tail+1) % (*TopicQueue)->size == head){

        // If incrementing the tail makes it equal to max size, wrap around and assign tail to 0
        if(tail +1 == (*TopicQueue)->size){
            (*TopicQueue)->tail = 0;
        
        } else {
            (*TopicQueue)->tail ++;
        }
    
    // If the TopicQueue is full, we set the appropriate variable
    } else {
        isFull = 1;
    }

    // Now that we've updated the tail index, we can enqueue the new TopicEntry
    // at the tail index (Unless it's full)
    if(isFull){
        returnVal = 0;
    
    } else {
        // Assign new Entry a number equal to the monotomically increasing entryCount
        (*TopicQueue)->entries[(*TopicQueue)->tail]->entryNum = (*TopicQueue)->entryCount;
        (*TopicQueue)->entryCount++;
        // Update time stamp for new Entry
        gettimeofday(&(*TopicQueue)->entries[(*TopicQueue)->tail]->timeStamp, NULL);
        (*TopicQueue)->entries[(*TopicQueue)->tail]->pubID = (*Entry)->pubID;
        // Set appropriate photoURL and photoCaption
        strcpy((*TopicQueue)->entries[(*TopicQueue)->tail]->photoCaption, (*Entry)->photoCaption); 
        strcpy((*TopicQueue)->entries[(*TopicQueue)->tail]->photoURL, (*Entry)->photoURL); 

        // Since everything is good, set returnVal to 1
        returnVal = 1;
    }

    // Now that we're done messing with stuff, release the TopicQueue and return
    pthread_mutex_unlock(&(*TopicQueue)->lock);
    return returnVal;
}

int getEntry(TopicQueue** TopicQueue, int lastEntry, Entry** emptyEntry){

    
    // Keeps track of whether or not the next entry to retrieve is in the queue
    int entryFound = 0;

    int entryCount, returnVal, currentIndex, i;

    // Lock up the TopicQueue before changing stuff
    pthread_mutex_lock(&(*TopicQueue)->lock);

    // Calculate the number of entries in TopicQueue//
    // If the head is less than/eaual to the tail, set entryCount to tail-head + 1;
    if((*TopicQueue)->head <= (*TopicQueue)->tail){
        entryCount = (*TopicQueue)->tail - (*TopicQueue)->head + 1;
    
    // Otherwise, we need to take capacity into account
    } else {
        entryCount = (*TopicQueue)->tail - (*TopicQueue)->head + (*TopicQueue)->size + 1;
    }

    // Case 1​: ​topic queue is empty​ - ​getEntry()​ will return 0.
    if((*TopicQueue)->head == -1){
        returnVal = 0;

    // Otherwise, we can look for an entry
    } else {

        // Look through all entries
        for(i = 0; i < entryCount; i ++){
            currentIndex = ((*TopicQueue)->head + i) % (*TopicQueue)->size;
            
            // If there's an entry who's entryNum == lastEntry + 1, then we've found it
            if((*TopicQueue)->entries[currentIndex]->entryNum == lastEntry + 1){
                entryFound = 1;
                break;
            }
        }

        /*Case 2​: ​lastEntry+1​​entry is in the queue - ​getEntry()​ will scan thequeue 
        entries, starting with the oldest entry in the queue, until it finds the
        lastentry+1​ entry, then it copies the entry into the empty ​topicEntrystructure 
        passed to our routine and return 1
        */  
        if(entryFound){
            setEntryPubID(emptyEntry, getEntryPubID(&(*TopicQueue)->entries[currentIndex]));
            setEntryNum(emptyEntry, (*TopicQueue)->entries[currentIndex]->entryNum);
            setEntryTimeStamp(emptyEntry, &(*TopicQueue)->entries[currentIndex]->timeStamp);
            strcpy((*emptyEntry)->photoCaption, (*TopicQueue)->entries[currentIndex]->photoCaption);
            strcpy((*emptyEntry)->photoURL, (*TopicQueue)->entries[currentIndex]->photoURL);

            returnVal = 1;
        
        
        /*Case 3​: ​topic queue is not empty and ​lastentry+1​ entry is not the queue​ - For this case, 
        there are 2 possible sub-cases:*/
        } else {

            for(i = 0; i < entryCount; i++){
                currentIndex = ((*TopicQueue)->head + i) % (*TopicQueue)->size;
                if((*TopicQueue)->entries[currentIndex]->entryNum > lastEntry + 1){
                    entryFound = 1;
                    break;
                }
            }

            /*Sub-case (i): getEntry()​ will scan the queue entries, starting with the oldest entry in the queue. 
            If all entries in the queue are less than or equal to lastentry+1​, that entry has yet to 
            be put into the queue andgetEntry()​ will return 0. (Note, this is like the queue is empty.)
            */
            if(!entryFound){
                returnVal = 0;
            

            /*(ii) getEntry()​ will scan the queue entries, starting with the oldest entry in the queue. 
            If the first entry encountered has an entry number greater thanlastEntry+1​, copy that 
            entry into our empty ​topicEntry​ struct andreturn the ​entryNum​ of that entry. (​Note​: This 
            case occurs because thelastEntry+1​ entry was dequeued by the cleanup thread (see below).
            The calling thread should update its ​lastEntry​ to the ​entryNum​. Ifyou think about this case, 
            the first entry that is greater thanlastentry+1​ will be the oldest entry in the queue.)
            */
            } else {
                setEntryPubID(emptyEntry, (*TopicQueue)->entries[currentIndex]->pubID);
                setEntryNum(emptyEntry, (*TopicQueue)->entries[currentIndex]->entryNum);
                setEntryTimeStamp(emptyEntry, &(*TopicQueue)->entries[currentIndex]->timeStamp);
                strcpy((*emptyEntry)->photoCaption, (*TopicQueue)->entries[currentIndex]->photoCaption);
                strcpy((*emptyEntry)->photoURL, (*TopicQueue)->entries[currentIndex]->photoURL);

                returnVal = (*TopicQueue)->entries[currentIndex]->entryNum;
            }
        }
    }

    // unlock the Topic Queue and return
    pthread_mutex_unlock(&(*TopicQueue)->lock);
    return returnVal;
    
}

int dequeue(TopicQueue** TopicQueue, suseconds_t delta){

    // Set up variable declarations before messing with TopicQueue
    int entryCount, returnVal, currentIndex;
    int i = 0;
    struct timeval time;
    long int age;

    // Lock up the topic queue
    pthread_mutex_lock(&(*TopicQueue)->lock);

    // Calculate the number of entries in TopicQueue//
    // If the head is less than/eaual to the tail, set entryCount to tail-head + 1;
    if((*TopicQueue)->head <= (*TopicQueue)->tail){
        entryCount = (*TopicQueue)->tail - (*TopicQueue)->head + 1;
    
    // Otherwise, we need to take capacity into account
    } else {
        entryCount = (*TopicQueue)->tail - (*TopicQueue)->head + (*TopicQueue)->size + 1;
    }

    // Next, we need to move onto the actual dequeuing
    // IF empty, do nothing
    if ((*TopicQueue)->head == -1){
        returnVal = 0;
    
    // Otherwise, we need to start by parsing all of the entries from oldest to newest
    } else {

        for(i = 0; i < entryCount; i++){
            currentIndex = (((*TopicQueue)->head + i) % (*TopicQueue)->size);

            // retrieve age of entry
            gettimeofday(&time, NULL);
            age = (long int) (time.tv_sec - (*TopicQueue)->entries[currentIndex]->timeStamp.tv_sec) * 1000000 + (long int) (time.tv_usec - (*TopicQueue)->entries[currentIndex]->timeStamp.tv_usec);

            // If there comes along an entry that's too young, all entries after that aren't either, so skip.
            if((suseconds_t) age < delta){
                break;
            }
        }

        // Case 1: Every entry in the TopicQueue isn't old enough to be dequeued.
        if(i == 0){
            returnVal = 0;
        
        // Case 2: Every entry is old enough to dequeue (unlikely but here we are)
        } else if(i== entryCount) {
            (*TopicQueue)->head = -1;
            (*TopicQueue)->tail = 0;

            returnVal = 1;
        
        // Case 3: Simply update the head to the index, dequeueing everything up to index-1
        } else {
            (*TopicQueue)->head = currentIndex;
            returnVal = 1;
        }
    }

    // Unlock the Topic Queue
    pthread_mutex_unlock(&(*TopicQueue)->lock);
    return returnVal;
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
