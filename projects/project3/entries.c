#include <sys/time.h>
#include <string.h>
#include "entries.h"

/* --------------- topicEntry Setters --------------- */
void setEntryTimeStamp(topicEntry** Entry, struct timeval newTimeStamp){
    (*Entry)->timeStamp = newTimeStamp;
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
