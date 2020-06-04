#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>
#include "entries.h"

int main(int argc, char **argv){

    /* ---- Initialize entry variables ---- */
    struct timeval entryTimeStamp;
    int entryNum = 0;
    

    // Allocate memory for new entry
    topicEntry* E1 = (topicEntry*) malloc(sizeof(topicEntry));
    entryNum++;

    // initialize E1_photoURL
    char* E1_photoURL = "www.google.com";
    // initialize E1_caption
    char* E1_caption = "yo yo yo what up ya\'ll";

    /* ----  Initialize new entry ---- */

    // Start with setting time.
    gettimeofday(&entryTimeStamp, NULL);
    setEntryTimeStamp(&E1, entryTimeStamp);

    // Next set entry num
    setEntryNum(&E1, entryNum);

    // Next setPubID
    setEntryPubID(&E1, 11111);

    // Next set URL
    setEntryPhotoURL(&E1, &E1_photoURL);

    // Next set photo caption
    setEntryPhotoCaption(&E1, &E1_caption);

    /* ------------------------------- */

    // Print Entry time stamp in seconds
    fprintf(stdout, "Time: %li\n", getEntryTimeStamp(&E1).tv_sec);
    fprintf(stdout, "Entry Num: %i\n", getEntryNum(&E1));
    fprintf(stdout, "Entry PubID: %i\n", getEntryPubID(&E1));
    fprintf(stdout, "Entry Photo URL: %s\n", getEntryPhotoURL(&E1));
    fprintf(stdout, "Entry Caption: %s\n", getEntryPhotoCaption(&E1));

    // Free memory from entry
    free(E1);
}