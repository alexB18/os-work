#include <sys/time.h>
#include <stdbool.h>
#include "Entry.h"

#ifndef MAXENTRIES
#define MAXENTRIES 10  // buffer size
#endif

typedef struct Buffer {
    bool isFull;
    int entryCount, head, tail, highestEntryNum;
    struct topicEntry** entries;
} Buffer;

/* --------------- Buffer Constructor/Destructor -------------- */
Buffer* constructBuffer();
void initializeBuffer(Buffer** Buffer);
void destroyBuffer(Buffer** Buffer);
/* ------------------------------------------------------------ */

int enqueue(Buffer** Buffer, Entry** Entry);
int dequeue(Buffer** Buffer);

/* --------------- Buffer Getters and Setters ----------------- */
int getBufferEntryCount(Buffer** Buffer);
int getBufferHeadIndex(Buffer** Buffer);
int getBufferTailIndex(Buffer** Buffer);
int getBufferhighestEntryNum(Buffer** Buffer);
int getBufferSize(Buffer** Buffer);

int incrementBufferEntryCount(Buffer** Buffer);
int decrementBufferEntryCount(Buffer** Buffer);
void setBufferHeadIndex(Buffer** Buffer, int head);
void setBufferTailIndex(Buffer** Buffer, int tail);
void incrementBufferhighestEntryNum(Buffer** Buffer);
void incrementHeadPointer(Buffer** Buffer);
void decrementTailPointer(Buffer** Buffer);
/* ------------------------------------------------------------ */

/* --------------------- Buffer Helpers ---------------------- */
void printLimitedBufferStatus(Buffer** Buffer);
void printFullBufferStatus(Buffer** Buffer);

bool isFull(Buffer** Buffer);
bool isEmpty(Buffer** Buffer);
/* ------------------------------------------------------------ */