#include <sys/time.h>
#include <stdbool.h>
#include "Entry.h"

#ifndef MAXENTRIES
#define MAXENTRIES 10  // TopicQueue size
#endif

typedef struct TopicQueue {
    bool isFull;
    int entryCount, head, tail, highestEntryNum;
    struct topicEntry** entries;
} TopicQueue;

/* --------------- TopicQueue Constructor/Destructor -------------- */
TopicQueue* constructTopicQueue();
void initializeTopicQueue(TopicQueue** TopicQueue);
void destroyTopicQueue(TopicQueue** TopicQueue);
/* ------------------------------------------------------------ */

int enqueue(TopicQueue** TopicQueue, Entry** Entry);
int dequeue(TopicQueue** TopicQueue);

/* --------------- TopicQueue Getters and Setters ----------------- */
int getTopicQueueEntryCount(TopicQueue** TopicQueue);
int getTopicQueueHeadIndex(TopicQueue** TopicQueue);
int getTopicQueueTailIndex(TopicQueue** TopicQueue);
int getTopicQueuehighestEntryNum(TopicQueue** TopicQueue);
int getTopicQueueSize(TopicQueue** TopicQueue);

int incrementTopicQueueEntryCount(TopicQueue** TopicQueue);
int decrementTopicQueueEntryCount(TopicQueue** TopicQueue);
void setTopicQueueHeadIndex(TopicQueue** TopicQueue, int head);
void setTopicQueueTailIndex(TopicQueue** TopicQueue, int tail);
void incrementTopicQueuehighestEntryNum(TopicQueue** TopicQueue);
void incrementHeadPointer(TopicQueue** TopicQueue);
void decrementTailPointer(TopicQueue** TopicQueue);
/* ------------------------------------------------------------ */

/* --------------------- TopicQueue Helpers ---------------------- */
void printLimitedTopicQueueStatus(TopicQueue** TopicQueue);
void printFullTopicQueueStatus(TopicQueue** TopicQueue);

bool isFull(TopicQueue** TopicQueue);
bool isEmpty(TopicQueue** TopicQueue);
/* ------------------------------------------------------------ */