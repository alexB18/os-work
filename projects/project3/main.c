#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/time.h>
#include <string.h>
#include "Buffer.h"

#define NUMBUFFERS 10

struct Buffer** Buffers; // buffers

pthread_mutex_t mutex[NUMBUFFERS]; //mutex locks for buffers
sem_t full[NUMBUFFERS]; // full semaphores
sem_t empty[NUMBUFFERS]; // empty semaphores

int main(int argc, char **argv){

    Buffers = (Buffer**) malloc(NUMBUFFERS * sizeof(Buffer*));
    for(int i = 0; i < NUMBUFFERS; i++){

        // Allocate memory for each Buffer
        Buffers[i] = (Buffer*) malloc(sizeof(Buffer));

        // Initialize each Buffer
        initializeBuffer(&(Buffers[i]));
    }

    // Create the buffer semaphores
    for(int i = 0; i < NUMBUFFERS; i++){
        pthread_mutex_init(&(mutex[i]), NULL);
    }

    // Destroy Each Buffer
    for(int i = 0; i < NUMBUFFERS; i++){
        destroyBuffer(&(Buffers[i]));
    }
    free(Buffers);


}