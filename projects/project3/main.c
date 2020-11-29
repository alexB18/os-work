#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/time.h>
#include <string.h>
#include "Buffer.h"

#define NUMBUFFERS 5

struct Buffer** Buffers; // buffers

pthread_mutex_t mutex[NUMBUFFERS]; //mutex locks for buffers
sem_t full[NUMBUFFERS]; // full semaphores
sem_t empty[NUMBUFFERS]; // empty semaphores

int MODE;

int usage(int argc, char** argv){

    if(argc == 1){
        return 0;

    } else if(argc == 2){

        fprintf(stderr, 
            "usage: %s <flag> <output file>\n", 
            argv[0]);
        exit(EXIT_FAILURE);
    
    } else if(argc == 3){

        if(strcmp(argv[1], "-f") != 0){

            fprintf(stderr, 
                "usage: %s <flag> <output file>\n", 
                argv[0]);
            exit(EXIT_FAILURE);
        }

    }
    return 1;
}

int main(int argc, char **argv){

    // Check for correct usage
    MODE = usage(argc, argv);

    // If -f is received, we want to output to a File
    if(MODE == 1){

        //Init input and output file names
        char* outFileName = argv[2];

        // Initialize outFilePointer
        FILE *outFilePointer;
        outFilePointer = freopen(outFileName, "w+", stdout);

        // Check if outFilepointer was created successfully
        if(outFilePointer == NULL){
            fprintf(stderr, "freopen() failed to create/open file %s\n", outFileName);
            exit(EXIT_FAILURE);
        }

    }

    Buffers = (Buffer**) malloc(NUMBUFFERS * sizeof(Buffer*));
    for(int i = 0; i < NUMBUFFERS; i++){

        // Construct each Buffer
        Buffers[i] = constructBuffer();
    }

    // Create the buffer semaphores
    for(int i = 0; i < NUMBUFFERS; i++){
        pthread_mutex_init(&(mutex[i]), NULL);
        sem_init(&full[i], 0, 0);
        sem_init(&empty[i], 0, MAXENTRIES);
    }

    // Print the status of each Buffer
    for(int i = 0; i < NUMBUFFERS; i++){
        fprintf(stdout, "Buffer[%i]\n", i);
        printFullBufferStatus(&Buffers[i]);
        fprintf(stdout, "\n");
    }

    // Destroy Each Buffer
    for(int i = 0; i < NUMBUFFERS; i++){
        destroyBuffer(&(Buffers[i]));
    }
    free(Buffers);


}