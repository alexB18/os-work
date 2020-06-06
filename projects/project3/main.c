#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>
#include "topics.h"

int main(int argc, char **argv){

    /* ---- Initialize entry variables ---- */
    //struct timeval entryTimeStamp;
    int entryNum = 0;

    // initialize E0 Strings
    char* E0_photoURL = "www.google.com";
    char* E0_caption = "yo yo yo what up ya\'ll.";

    // initialize E1 Strings
    char* E1_photoURL = "www.mytesturl.org";
    char* E1_caption = "This caption is a test.";
    
    // initialize E2 Strings
    char* E2_photoURL = "www.clubpenguin.com";
    char* E2_caption = "Flip the iceburg!";

    // Allocate memory for new entries & initialize attributes
    // Start by declaring topicEntry pointers
    topicEntry* E0;
    topicEntry* E1;
    topicEntry* E2;

    // E0
    initializeEntry(&E0, entryNum, 00000);
    setEntryPhotoURL(&E0, &E0_photoURL);
    setEntryPhotoCaption(&E0, &E0_caption);
    entryNum++;

    // E1
    initializeEntry(&E1, entryNum, 11111);
    setEntryPhotoURL(&E1, &E1_photoURL);
    setEntryPhotoCaption(&E1, &E1_caption);
    entryNum++;

    // E2
    initializeEntry(&E2, entryNum, 22222);
    setEntryPhotoURL(&E2, &E2_photoURL);
    setEntryPhotoCaption(&E2, &E2_caption);
    entryNum++;
    
    printEntryStatus(&E0);
    printEntryStatus(&E1);
    printEntryStatus(&E2);

    // Free memory from entry
    freeEntry(&E0);
    freeEntry(&E1);
    freeEntry(&E2);
}