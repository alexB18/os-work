#include <sys/time.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "Entry.h"

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
    strcpy((*Entry)->photoURL, *newPhotoURL);
}

void setEntryPhotoCaption(Entry** Entry, char** newPhotoCaption){
    strcpy((*Entry)->photoCaption, *newPhotoCaption);
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
