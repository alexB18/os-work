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

    Entry* Entry1 = constructEntry();
    enqueue(&(Buffers[0]), &Entry1);

    // Am having problem of creating new Entries
    // Gonna change constructor to return Entry


    // Print the status of each Buffer
    for(int i = 0; i < NUMBUFFERS; i++){
        fprintf(stdout, "Buffer[%i]\n", i);
        printFullBufferStatus(&Buffers[i]);
        fprintf(stdout, "\n");
    }

    dequeue(&(Buffers[0]));

    // Destroy Each Buffer
    for(int i = 0; i < NUMBUFFERS; i++){
        destroyBuffer(&(Buffers[i]));
    }
    free(Buffers);


}