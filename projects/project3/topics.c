#include <sys/time.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "topics.h"

/* --------------- TopicEntry Setters --------------- */
void setEntryTimeStamp(TopicEntry** Entry, struct timeval* newTimeStamp){

    memcpy(&(*Entry)->timeStamp, newTimeStamp, sizeof(*newTimeStamp));
}

void setEntryNum(TopicEntry** Entry, int newEntryNum){
    (*Entry)->entryNum = newEntryNum;
}

void setEntryPubID(TopicEntry** Entry, int newPubID){
    (*Entry)->pubID = newPubID;
}

void setEntryPhotoURL(TopicEntry** Entry, char** newPhotoURL){
    strcpy((*Entry)->photoURL, *newPhotoURL);
}

void setEntryPhotoCaption(TopicEntry** Entry, char** newPhotoCaption){
    strcpy((*Entry)->photoCaption, *newPhotoCaption);
}

void initializeEntry(TopicEntry** Entry, int newEntryNum, int newPubID){
    
    // Start by allocating memory for the new Entry...
    (*Entry) = (TopicEntry*) malloc(sizeof(TopicEntry));

    // Next, allocate memory for both the photoURL and the photoCaption
    (*Entry)->photoURL = (char*) malloc(URLSIZE * sizeof(char));
    (*Entry)->photoCaption = (char*) malloc(CAPSIZE * sizeof(char));

    // Retrieve current time
    struct timeval entryTimeStamp;
    gettimeofday(&entryTimeStamp, NULL);
    setEntryTimeStamp(Entry, &entryTimeStamp);

    // Set new entry num
    setEntryNum(Entry, newEntryNum);

    // Set new pub id
    setEntryPubID(Entry, newPubID);

}

void freeEntry(TopicEntry** Entry){

    // Start by freeing memory from both the photoURL and the photoCaption
    free((*Entry)->photoURL);
    free((*Entry)->photoCaption);

    // Finally, free self
    free((*Entry));

}
/* -------------------------------------------------- */


/* --------------- TopicEntry Getters --------------- */
struct timeval getEntryTimeStamp(TopicEntry** Entry){
    return (*Entry)->timeStamp;
}

int getEntryNum(TopicEntry** Entry){
    return (*Entry)->entryNum;
}

int getEntryPubID(TopicEntry** Entry){
    return (*Entry)->pubID;
}

char* getEntryPhotoURL(TopicEntry** Entry){
    return (*Entry)->photoURL;
}

char* getEntryPhotoCaption(TopicEntry** Entry){
    return (*Entry)->photoCaption;
}
/* -------------------------------------------------- */

/* --------------- TopicEntry Helpers --------------- */
void printEntryStatus(TopicEntry** Entry){

    // Print Entry time stamp in seconds.milliseconds
    fprintf(stdout, "Time: %li.%li s\n", getEntryTimeStamp(Entry).tv_sec, getEntryTimeStamp(Entry).tv_usec);
    fprintf(stdout, "Entry Num: %i\n", getEntryNum(Entry));
    fprintf(stdout, "Entry PubID: %i\n", getEntryPubID(Entry));
    fprintf(stdout, "Entry Photo URL: %s\n", getEntryPhotoURL(Entry));
    fprintf(stdout, "Entry Caption: %s\n", getEntryPhotoCaption(Entry));
    fprintf(stdout, "\n");
}
/* -------------------------------------------------- */
