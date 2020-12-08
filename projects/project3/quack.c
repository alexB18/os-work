#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <signal.h>
#include <time.h>
#include "quack.h"

TopicQueue* Topic0;

// initialize a ThreadPool
int initializeThreadPool(ThreadPool* newPool){

   newPool->fileCount = 0;
   newPool->nextFile = 0;

   // Initialize lock
   pthread_mutexattr_t attr;
   pthread_mutexattr_init(&attr);
   pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_ERRORCHECK);
   pthread_mutexattr_setrobust(&attr, PTHREAD_MUTEX_ROBUST);
   pthread_mutex_init(&newPool->lock, &attr);
   pthread_mutexattr_destroy(&attr);

   return 0;
}

void destroyThreadPool(ThreadPool* Pool){

   // wait for each thread to finish
   for(int i = 0; i < MAXWORKING; i++){
      pthread_join(Pool->threads[i], NULL);
   }
   // One they have, destroy the pool's mutex
   pthread_mutex_destroy(&Pool->lock);
}


// Publisher thread function
// Will enqueue
void* pub(void* publisherPool_VOID){
   struct timespec waitTime;
   waitTime.tv_sec = 0;
   int pubError = 0;

   fprintf(stdout, "Pub thread: (%li) here\n", pthread_self());

   Entry* newEntry = constructEntry();
   char* newEntry_caption = "test";
   char* newEntry_URL = "https://www.google.com";
   setEntryPhotoCaption(&newEntry, &newEntry_caption);
   setEntryPhotoURL(&newEntry, &newEntry_URL);
   newEntry->pubID = pthread_self();

   // Sometimes the publisher might be unable to push to a full queue
   // So, let's continuously try, and give a bit of waiting time after each go
   for(int i = 0; i < 30; i++){
      pubError = enqueue(&Topic0, &newEntry);
      // If it worked, report so and break
      if(pubError == 1){
         fprintf(stdout, "Publisher: %ld enqueued Entry to topic: %d\n", pthread_self(), Topic0->id);
      }
      
      // otherwise, try again after 50 ms
      waitTime.tv_nsec = 100000000;
      nanosleep(&waitTime, NULL);
   }

   // If after all this time, we've still failed, print an error
   if(pubError == 0){
      fprintf(stderr, "ERROR, Publisher: %ld unable to enqueue Entry to topid: %d\n", pthread_self(), Topic0->id);
   }

   // Since enqueue copies an existing Entry, we need to destroy newEntry
   destroyEntry(&newEntry);

   // finally, give up processor
   sched_yield();

   /*
   Entry* Entry1 = constructEntry();
   char* Entry1_caption = "test1";
   char* Entry1_url = "https://www.google.com";
   setEntryPhotoURL(&Entry1, &Entry1_url);
   setEntryPhotoCaption(&Entry1, &Entry1_caption);

   Entry* Entry2 = constructEntry();
   char* Entry2_caption = "test2";
   char* Entry2_url = "https://www.google.com";
   setEntryPhotoURL(&Entry2, &Entry2_url);
   setEntryPhotoCaption(&Entry2, &Entry2_caption);
   */


   //enqueue(&Topic0, &newEntry);
   /*enqueue(&Topic0, &Entry1);
   enqueue(&Topic0, &Entry2);
   */

   // enqueue simply copies, so we need to free Entry0
   //destroyEntry(&newEntry);
   /*
   destroyEntry(&Entry1);
   destroyEntry(&Entry2);
   */

   return NULL;
}

// Subscriber thread function
void* sub(void* subscriberPool_VOID){
   struct timespec waitTime;
   waitTime.tv_sec = 0;
   int subError = 0;

   fprintf(stdout, "Sub thread: (%li) here\n", pthread_self());

   Entry* grabbedEntry = constructEntry();
   initializeEntry(&grabbedEntry);
   //printFullTopicQueueStatus(&Topic0);

   // Sometimes the subscriber might be unable to pull from an empty queue
   // So, let's continuously try, and give a bit of waiting time after each go
   for(int i = 0; i < 30; i++){
      subError = getEntry(&Topic0, Topic0->highestEntryNum, &grabbedEntry);
      // If it worked, report so and break
      if(subError == 1){
         fprintf(stdout, "Subscriber: %ld pulled Entry %d,\nURL: %s\nCaption: %s\n", pthread_self(), grabbedEntry->entryNum, grabbedEntry->photoURL, grabbedEntry->photoCaption);
         break;
      
      }
      // otherwise, try again after 50 ms
      waitTime.tv_nsec = 100000000;
      nanosleep(&waitTime, NULL);
   }

   if(subError == 0){
      fprintf(stderr, "ERROR, Subscriber: %ld unable to pull latest Entry from Topic: %d.\n", pthread_self(), Topic0->id);
   }

   destroyEntry(&grabbedEntry);
   // finally, yield processor
   sched_yield();

   return NULL;
}

// Cleanup thread function
void* cleanup(void* delta_VOID){
   return NULL;
}

// Publisher spawning function
int spawnSubs(ThreadPool* Pool){

   for(int i = 0 ; i < MAXWORKING; i++){
      pthread_create(&Pool->threads[i], NULL, &sub, NULL);
   }

   fprintf(stdout, "Congrats! Subs have been spawned.\n");
   return 1;
}

// Subscriber Spawning function
int spawnPubs(ThreadPool* Pool){

   for(int i = 0 ; i < MAXWORKING; i++){
      pthread_create(&Pool->threads[i], NULL, &pub, NULL);
   }

   fprintf(stdout, "Congrats! Pubs have been spawned.\n");
   return 1;
}


int main(){

   Topic0 = constructTopicQueue(1, "test", 5);
   initializeTopicQueue(&Topic0);



   //10 Entries for test

   // Create/Populate pub/sub pools
   ThreadPool pubPool;
   ThreadPool subPool;
   initializeThreadPool(&pubPool);
   initializeThreadPool(&subPool);
   spawnPubs(&pubPool);
   spawnSubs(&subPool);

   sleep(3);

   // Waait for pubs/subs to finish then destroy
   destroyThreadPool(&pubPool);
   destroyThreadPool(&subPool);

   printFullTopicQueueStatus(&Topic0);

   // Destroy the communal TopicQueue
   destroyTopicQueue(&Topic0);



   /*
   // TopicQueue* Topics;
   //pthread_t cleaner;
   pthread_t pubber;
   pthread_t subber;

   // Create a single pub thread
   pthread_create(&pubber, NULL, &pub, NULL);
   // Create a single sub thread
   pthread_create(&subber, NULL, &sub, NULL);
   */
   return 1;
}
