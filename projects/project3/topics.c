#include <sys/time.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "topics.h"

/* --------------- topicEntry Setters --------------- */
void setEntryTimeStamp(topicEntry** Entry, struct timeval* newTimeStamp){

    memcpy(&(*Entry)->timeStamp, newTimeStamp, sizeof(*newTimeStamp));
}

void setEntryNum(topicEntry** Entry, int newEntryNum){
    (*Entry)->entryNum = newEntryNum;
}

void setEntryPubID(topicEntry** Entry, int newPubID){
    (*Entry)->pubID = newPubID;
}

void setEntryPhotoURL(topicEntry** Entry, char** newPhotoURL){
    strcpy((*Entry)->photoURL, *newPhotoURL);
}

void setEntryPhotoCaption(topicEntry** Entry, char** newPhotoCaption){
    strcpy((*Entry)->photoCaption, *newPhotoCaption);
}
/* -------------------------------------------------- */


/* --------------- topicEntry Getters --------------- */
struct timeval getEntryTimeStamp(topicEntry** Entry){
    return (*Entry)->timeStamp;
}

int getEntryNum(topicEntry** Entry){
    return (*Entry)->entryNum;
}

int getEntryPubID(topicEntry** Entry){
    return (*Entry)->pubID;
}

char* getEntryPhotoURL(topicEntry** Entry){
    return (*Entry)->photoURL;
}

char* getEntryPhotoCaption(topicEntry** Entry){
    return (*Entry)->photoCaption;
}
/* -------------------------------------------------- */

/* --------------- topicEntry Helpers --------------- */
void printEntryStatus(topicEntry** Entry){

    // Print Entry time stamp in seconds.milliseconds
    fprintf(stdout, "Time: %li.%li s\n", getEntryTimeStamp(Entry).tv_sec, getEntryTimeStamp(Entry).tv_usec);
    fprintf(stdout, "Entry Num: %i\n", getEntryNum(Entry));
    fprintf(stdout, "Entry PubID: %i\n", getEntryPubID(Entry));
    fprintf(stdout, "Entry Photo URL: %s\n", getEntryPhotoURL(Entry));
    fprintf(stdout, "Entry Caption: %s\n", getEntryPhotoCaption(Entry));
    fprintf(stdout, "\n");
}
/* -------------------------------------------------- */
