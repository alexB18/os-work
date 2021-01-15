#include "topic_store.h"

// Number of spoons for spaghetti
#define MAXWORKING 1

#define MAXPUBLISHERS 1
#define MAXSUBSCRIBERS 1

#define NUMQUEUES 1

typedef struct ThreadPool {
   int fileCount;
   int nextFile;
   //char* files[MAXPUBLISHERS];
   pthread_t threads[MAXWORKING];
   int isFree[MAXWORKING];
   pthread_mutex_t lock;

} ThreadPool;

// pub/sub thread functions
// (Ie. instructions on what pubs/subs should do)
void* pub();
void* sub();

// cleaning thread function
void* cleanup(void* delta_VOID);

// initialize a ThreadPool
int initializeThreadPool(ThreadPool* newPool);

// destroy a ThreadPool
void destroyThreadPool(ThreadPool* Pool);