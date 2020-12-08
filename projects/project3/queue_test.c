#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/time.h>
#include <string.h>
#include "threads.h"

#define NUMQUEUES 1

struct TopicQueue** TopicQueues; // TopicQueues

pthread_mutex_t mutex[NUMQUEUES]; //mutex locks for TopicQueues
sem_t full[NUMQUEUES]; // full semaphores
sem_t empty[NUMQUEUES]; // empty semaphores

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

/*
int *publisher(){

}

int *subscriber(){

}

int *cleanup(){

}
*/

int main(int argc, char **argv){

    TopicQueues = (TopicQueue**) malloc(NUMQUEUES * sizeof(TopicQueue*));
    for(int i = 0; i < NUMQUEUES; i++){

        // Allocate memory for each TopicQueue
        TopicQueues[i] = constructTopicQueue(-1, "NULL", MAXENTRIES);
    }

    // Create the TopicQueue semaphores
    for(int i = 0; i < NUMQUEUES; i++){
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
    
    
    Entry* Entry1 = constructEntry();
    char* Entry1_caption = "hold onto ur butts!";
    char* Entry1_url = "https://www.google.com";
    setEntryPhotoURL(&Entry1, &Entry1_url);
    setEntryPhotoCaption(&Entry1, &Entry1_caption);
    enqueue(&(TopicQueues[0]), &Entry1);
    
    Entry* Entry2 = constructEntry();
    char* Entry2_caption = "hold onto ur butts!";
    char* Entry2_url = "https://www.google.com";
    setEntryPhotoURL(&Entry2, &Entry2_url);
    setEntryPhotoCaption(&Entry2, &Entry2_caption);
    

    Entry* Entry3 = constructEntry();
    char* Entry3_caption = "hold onto ur butts!";
    char* Entry3_url = "https://www.google.com";
    setEntryPhotoURL(&Entry3, &Entry3_url);
    setEntryPhotoCaption(&Entry3, &Entry3_caption);

    Entry* Entry4 = constructEntry();
    char* Entry4_caption = "hold onto ur butts!";
    char* Entry4_url = "https://www.google.com";
    setEntryPhotoURL(&Entry4, &Entry4_url);
    setEntryPhotoCaption(&Entry4, &Entry4_caption);

    Entry* Entry5 = constructEntry();
    char* Entry5_caption = "hold onto ur butts!";
    char* Entry5_url = "https://www.google.com";
    setEntryPhotoURL(&Entry5, &Entry5_url);
    setEntryPhotoCaption(&Entry5, &Entry5_caption);

    Entry* Entry6 = constructEntry();
    char* Entry6_caption = "hold onto ur butts!";
    char* Entry6_url = "https://www.google.com";
    setEntryPhotoURL(&Entry6, &Entry6_url);
    setEntryPhotoCaption(&Entry6, &Entry6_caption);

    Entry* Entry7 = constructEntry();
    char* Entry7_caption = "hold onto ur butts!";
    char* Entry7_url = "https://www.google.com";
    setEntryPhotoURL(&Entry7, &Entry7_url);
    setEntryPhotoCaption(&Entry7, &Entry7_caption);

    Entry* Entry8 = constructEntry();
    char* Entry8_caption = "hold onto ur butts!";
    char* Entry8_url = "https://www.google.com";
    setEntryPhotoURL(&Entry8, &Entry8_url);
    setEntryPhotoCaption(&Entry8, &Entry8_caption);

    Entry* Entry9 = constructEntry();
    char* Entry9_caption = "hold onto ur butts!";
    char* Entry9_url = "https://www.google.com";
    setEntryPhotoURL(&Entry9, &Entry9_url);
    setEntryPhotoCaption(&Entry9, &Entry9_caption);

    enqueue(&(TopicQueues[0]), &Entry0);
    enqueue(&(TopicQueues[0]), &Entry1);
    enqueue(&(TopicQueues[0]), &Entry2);
    enqueue(&(TopicQueues[0]), &Entry3);
    enqueue(&(TopicQueues[0]), &Entry4);
    enqueue(&(TopicQueues[0]), &Entry5);
    enqueue(&(TopicQueues[0]), &Entry6);
    enqueue(&(TopicQueues[0]), &Entry7);
    enqueue(&(TopicQueues[0]), &Entry8);
    enqueue(&(TopicQueues[0]), &Entry9);

    // Print the status of each TopicQueue
    for(int i = 0; i < NUMQUEUES; i++){
        fprintf(stdout, "TopicQueue[%i]\n", i);
        printFullTopicQueueStatus(&TopicQueues[i]);
        fprintf(stdout, "\n");
    }


    Entry* Entry10 = constructEntry();
    char* Entry10_caption = "hold onto ur butts!";
    char* Entry10_url = "https://www.google.com";
    setEntryPhotoURL(&Entry10, &Entry10_url);
    setEntryPhotoCaption(&Entry10, &Entry10_caption);

    Entry* Entry11 = constructEntry();
    char* Entry11_caption = "hold onto ur butts!";
    char* Entry11_url = "https://www.google.com";
    setEntryPhotoURL(&Entry11, &Entry11_url);
    setEntryPhotoCaption(&Entry11, &Entry11_caption);

    Entry* Entry12 = constructEntry();
    char* Entry12_caption = "hold onto ur butts!";
    char* Entry12_url = "https://www.google.com";
    setEntryPhotoURL(&Entry12, &Entry12_url);
    setEntryPhotoCaption(&Entry12, &Entry12_caption);
    
    Entry* Entry13 = constructEntry();
    char* Entry13_caption = "hold onto ur butts!";
    char* Entry13_url = "https://www.google.com";
    setEntryPhotoURL(&Entry13, &Entry13_url);
    setEntryPhotoCaption(&Entry13, &Entry13_caption);

    Entry* Entry14 = constructEntry();
    char* Entry14_caption = "hold onto ur butts!";
    char* Entry14_url = "https://www.google.com";
    setEntryPhotoURL(&Entry14, &Entry14_url);
    setEntryPhotoCaption(&Entry14, &Entry14_caption);

    Entry* Entry15 = constructEntry();
    char* Entry15_caption = "hold onto ur butts!";
    char* Entry15_url = "https://www.google.com";
    setEntryPhotoURL(&Entry15, &Entry15_url);
    setEntryPhotoCaption(&Entry15, &Entry15_caption);

    Entry* Entry16 = constructEntry();
    char* Entry16_caption = "hold onto ur butts!";
    char* Entry16_url = "https://www.google.com";
    setEntryPhotoURL(&Entry16, &Entry16_url);
    setEntryPhotoCaption(&Entry16, &Entry16_caption);

    Entry* Entry17 = constructEntry();
    char* Entry17_caption = "hold onto ur butts!";
    char* Entry17_url = "https://www.google.com";
    setEntryPhotoURL(&Entry17, &Entry17_url);
    setEntryPhotoCaption(&Entry17, &Entry17_caption);

    Entry* Entry18 = constructEntry();
    char* Entry18_caption = "hold onto ur butts!";
    char* Entry18_url = "https://www.google.com";
    setEntryPhotoURL(&Entry18, &Entry18_url);
    setEntryPhotoCaption(&Entry18, &Entry18_caption);

    Entry* Entry19 = constructEntry();
    char* Entry19_caption = "hold onto ur butts!";
    char* Entry19_url = "https://www.google.com";
    setEntryPhotoURL(&Entry19, &Entry19_url);
    setEntryPhotoCaption(&Entry19, &Entry19_caption);

    /*
    Entry* Entry20 = constructEntry();
    char* Entry20_caption = "hold onto ur butts!";
    char* Entry20_url = "https://www.google.com";
    setEntryPhotoURL(&Entry20, &Entry20_url);
    setEntryPhotoCaption(&Entry20, &Entry20_caption);

    Entry* Entry21 = constructEntry();
    char* Entry21_caption = "hold onto ur butts!";
    char* Entry21_url = "https://www.google.com";
    setEntryPhotoURL(&Entry21, &Entry21_url);
    setEntryPhotoCaption(&Entry21, &Entry21_caption);
    */



    fprintf(stdout, "\n\n\nWriting to full buffer\n\n\n");
    sleep(2);

    fprintf(stdout, "Enqueuing Entry: 10\n");
    sleep(.5);
    enqueue(&(TopicQueues[0]), &Entry10);

    fprintf(stdout, "Enqueuing Entry: 11\n");
    sleep(.5);
    enqueue(&(TopicQueues[0]), &Entry11);
    
    fprintf(stdout, "Enqueuing Entry: 12\n");
    sleep(.5);
    enqueue(&(TopicQueues[0]), &Entry12);

    fprintf(stdout, "Enqueuing Entry: 13\n");
    sleep(.5);
    enqueue(&(TopicQueues[0]), &Entry13);

    fprintf(stdout, "Enqueuing Entry: 14\n");
    sleep(.5);
    enqueue(&(TopicQueues[0]), &Entry14);

    fprintf(stdout, "Enqueuing Entry: 15\n");
    sleep(.5);
    enqueue(&(TopicQueues[0]), &Entry15);


    fprintf(stdout, "Enqueuing Entry: 16\n");
    sleep(.5);
    enqueue(&(TopicQueues[0]), &Entry16);

    fprintf(stdout, "Enqueuing Entry: 17\n");
    sleep(.5);
    enqueue(&(TopicQueues[0]), &Entry17);

    fprintf(stdout, "Enqueuing Entry: 18\n");
    sleep(.5);
    enqueue(&(TopicQueues[0]), &Entry18);


    fprintf(stdout, "Enqueuing Entry: 19\n");
    sleep(.5);
    enqueue(&(TopicQueues[0]), &Entry19);

    /*
    fprintf(stdout, "Enqueuing Entry: 20\n");
    sleep(.5);
    enqueue(&(TopicQueues[0]), &Entry20);

    fprintf(stdout, "Enqueuing Entry: 21\n");
    sleep(.5);
    enqueue(&(TopicQueues[0]), &Entry21);
    */
    
    


    // Print the status of each TopicQueue
    for(int i = 0; i < NUMQUEUES; i++){
        fprintf(stdout, "TopicQueue[%i]\n", i);
        printFullTopicQueueStatus(&TopicQueues[i]);
        fprintf(stdout, "\n");
    }

    /*
    for(int i= 0; i < 10; i++){
        dequeue(&(TopicQueues[0]), 1);
    }
    dequeue(&(TopicQueues)[0], 1);
    */

    // Print the status of each TopicQueue
    for(int i = 0; i < NUMQUEUES; i++){
        fprintf(stdout, "TopicQueue[%i]\n", i);
        printFullTopicQueueStatus(&TopicQueues[i]);
        fprintf(stdout, "\n");
    }

    //dequeue_tonowhere(&(TopicQueues[0]));

    // Destroy Each TopicQueue
    for(int i = 0; i < NUMQUEUES; i++){
        destroyTopicQueue(&(TopicQueues[i]));
    }
    free(TopicQueues);


}