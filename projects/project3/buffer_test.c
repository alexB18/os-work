#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>
#include "Buffer.h"

#define NUMBUFFERS 10

int main(int argc, char **argv){

    
    Buffer** Buffers = (Buffer**) malloc(NUMBUFFERS * sizeof(Buffer*));
    for(int i = 0; i < NUMBUFFERS; i++){

        // Allocate memory for each Buffer
        Buffers[i] = (Buffer*) malloc(sizeof(Buffer));

        // Initialize each Buffer
        initializeBuffer(&(Buffers[i]));
    }

    // Destroy Each Buffer
    for(int i = 0; i < NUMBUFFERS; i++){
        destroyBuffer(&(Buffers[i]));
    }
    free(Buffers);


}