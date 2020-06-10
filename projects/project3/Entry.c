#include <sys/time.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "Entry.h"

/* --------------- Entry Constructor/Destructor --------------- */
void initializeEntry(Entry** Entry){

    // allocate memory for URL and Caption
    (*Entry)->photoURL = (char*) malloc(URLSIZE + 1 * sizeof(char));
    (*Entry)->photoCaption = (char*) malloc(CAPSIZE + 1 * sizeof(char));

    // get execution time
    struct timeval executionTime;
    gettimeofday(&executionTime, NULL);

    // set Entry's attributes to defaults
    setEntryNum(Entry, -1);
    setEntryTimeStamp(Entry, &executionTime);
    setEntryPubID(Entry, -1);
    //setEntryPhotoURL(Entry, NULL);
    //setEntryPhotoCaption(Entry, NULL);
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
