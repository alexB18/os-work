#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/time.h>
#include <string.h>
#include "Buffer.h"

#define NUMBUFFERS 1

struct Buffer** Buffers; // buffers

pthread_mutex_t mutex[NUMBUFFERS]; //mutex locks for buffers
sem_t full[NUMBUFFERS]; // full semaphores
sem_t empty[NUMBUFFERS]; // empty semaphores

int main(int argc, char **argv){

    Buffers = (Buffer**) malloc(NUMBUFFERS * sizeof(Buffer*));
    for(int i = 0; i < NUMBUFFERS; i++){

        // Allocate memory for each Buffer
        Buffers[i] = constructBuffer();
    }

    // Create the buffer semaphores
    for(int i = 0; i < NUMBUFFERS; i++){
        pthread_mutex_init(&(mutex[i]), NULL);
        sem_init(&full[i], 0, 0);
        sem_init(&empty[i], 0, MAXENTRIES);
    }

    
    //10 Entries for test
    Entry* Entry0 = constructEntry();
    char* Entry0_caption = "hold onto ur butts!";
    char* Entry0_url = "https://www.google.com";
    setEntryPhotoURL(&Entry0, &Entry0_url);
    setEntryPhotoCaption(&Entry0, &Entry0_caption);
    enqueue(&(Buffers[0]), &Entry0);


    
    
    
    
    
    Entry* Entry1 = constructEntry();
    char* Entry1_caption = "hold onto ur butts!";
    char* Entry1_url = "https://www.google.com";
    setEntryPhotoURL(&Entry1, &Entry1_url);
    setEntryPhotoCaption(&Entry1, &Entry1_caption);
    enqueue(&(Buffers[0]), &Entry1);

    
    Entry* Entry2 = constructEntry();
    char* Entry2_caption = "hold onto ur butts!";
    char* Entry2_url = "https://www.google.com";
    setEntryPhotoURL(&Entry2, &Entry2_url);
    setEntryPhotoCaption(&Entry2, &Entry2_caption);
    enqueue(&(Buffers[0]), &Entry2);
    

    Entry* Entry3 = constructEntry();
    char* Entry3_caption = "hold onto ur butts!";
    char* Entry3_url = "https://www.google.com";
    setEntryPhotoURL(&Entry3, &Entry3_url);
    setEntryPhotoCaption(&Entry3, &Entry3_caption);
    enqueue(&(Buffers[0]), &Entry3);

    Entry* Entry4 = constructEntry();
    char* Entry4_caption = "hold onto ur butts!";
    char* Entry4_url = "https://www.google.com";
    setEntryPhotoURL(&Entry4, &Entry4_url);
    setEntryPhotoCaption(&Entry4, &Entry4_caption);
    enqueue(&(Buffers[0]), &Entry4);

    Entry* Entry5 = constructEntry();
    char* Entry5_caption = "hold onto ur butts!";
    char* Entry5_url = "https://www.google.com";
    setEntryPhotoURL(&Entry5, &Entry5_url);
    setEntryPhotoCaption(&Entry5, &Entry5_caption);
    enqueue(&(Buffers[0]), &Entry5);

    Entry* Entry6 = constructEntry();
    char* Entry6_caption = "hold onto ur butts!";
    char* Entry6_url = "https://www.google.com";
    setEntryPhotoURL(&Entry6, &Entry6_url);
    setEntryPhotoCaption(&Entry6, &Entry6_caption);
    enqueue(&(Buffers[0]), &Entry6);

    Entry* Entry7 = constructEntry();
    char* Entry7_caption = "hold onto ur butts!";
    char* Entry7_url = "https://www.google.com";
    setEntryPhotoURL(&Entry7, &Entry7_url);
    setEntryPhotoCaption(&Entry7, &Entry7_caption);
    enqueue(&(Buffers[0]), &Entry7);

    Entry* Entry8 = constructEntry();
    char* Entry8_caption = "hold onto ur butts!";
    char* Entry8_url = "https://www.google.com";
    setEntryPhotoURL(&Entry8, &Entry8_url);
    setEntryPhotoCaption(&Entry8, &Entry8_caption);
    enqueue(&(Buffers[0]), &Entry8);

    Entry* Entry9 = constructEntry();
    char* Entry9_caption = "hold onto ur butts!";
    char* Entry9_url = "https://www.google.com";
    setEntryPhotoURL(&Entry9, &Entry9_url);
    setEntryPhotoCaption(&Entry9, &Entry9_caption);
    enqueue(&(Buffers[0]), &Entry9);


    // Print the status of each Buffer
    for(int i = 0; i < NUMBUFFERS; i++){
        fprintf(stdout, "Buffer[%i]\n", i);
        printFullBufferStatus(&Buffers[i]);
        fprintf(stdout, "\n");
    }

    for(int i= 0; i < 10; i++){
        dequeue(&(Buffers[0]));
    }
    dequeue(&(Buffers)[0]);

    // Print the status of each Buffer
    for(int i = 0; i < NUMBUFFERS; i++){
        fprintf(stdout, "Buffer[%i]\n", i);
        printFullBufferStatus(&Buffers[i]);
        fprintf(stdout, "\n");
    }

    //dequeue(&(Buffers[0]));

    // Destroy Each Buffer
    for(int i = 0; i < NUMBUFFERS; i++){
        destroyBuffer(&(Buffers[i]));
    }
    free(Buffers);


}