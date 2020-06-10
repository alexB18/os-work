#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>
#include "Buffer.h"

int main(int argc, char **argv){

    /* ---- Initialize entry variables ---- */
    /*
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
    // Start by declaring Entry pointers
    Entry* E0 = (Entry*) malloc(sizeof(Entry));
    Entry* E1 = (Entry*) malloc(sizeof(Entry));
    Entry* E2 = (Entry*) malloc(sizeof(Entry));

    // Initialize Entries;
    initializeEntry(&E0);
    initializeEntry(&E1);
    initializeEntry(&E2);

    // E0
    setEntryNum(&E0, entryNum);
    setEntryPubID(&E0, 00000);
    setEntryPhotoURL(&E0, &E0_photoURL);
    setEntryPhotoCaption(&E0, &E0_caption);
    entryNum++;

    // E1
    setEntryNum(&E1, entryNum);
    setEntryPubID(&E1, 11111);
    setEntryPhotoURL(&E1, &E1_photoURL);
    setEntryPhotoCaption(&E1, &E1_caption);
    entryNum++;

    // E2
    setEntryNum(&E2, entryNum);
    setEntryPubID(&E2, 22222);
    setEntryPhotoURL(&E2, &E2_photoURL);
    setEntryPhotoCaption(&E2, &E2_caption);
    entryNum++;
    
    printEntryStatus(&E0);
    printEntryStatus(&E1);
    printEntryStatus(&E2);

    // Free memory from entry
    destroyEntry(&E0);
    destroyEntry(&E1);
    destroyEntry(&E2);
    */

    // Allocate memory for each Buffer
    Buffer* B0 = (Buffer*) malloc(sizeof(Buffer));
    Buffer* B1 = (Buffer*) malloc(sizeof(Buffer));
    Buffer* B2 = (Buffer*) malloc(sizeof(Buffer));

    // Initialize each Buffer
    initializeBuffer(&B0);
    initializeBuffer(&B1);
    initializeBuffer(&B2);

    // Destroy Each Buffer
    destroyBuffer(&B0);
    destroyBuffer(&B1);
    destroyBuffer(&B2);


}