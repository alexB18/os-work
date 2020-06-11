#include <sys/time.h>
#include "Entry.h"

#ifndef MAXENTRIES
#define MAXENTRIES 10  // buffer size
#endif

typedef struct Buffer {
    int entryCount, head, tail, insertedCount;
    struct Entry** entries;
} Buffer;

/* --------------- Buffer Constructor/Destructor -------------- */
void initializeBuffer(Buffer** Buffer);
void destroyBuffer(Buffer** Buffer);
/* ------------------------------------------------------------ */

/* --------------- Buffer Getters and Setters ----------------- */
int getBufferEntryCount(Buffer** Buffer);
int getBufferHeadIndex(Buffer** Buffer);
int getBufferTailIndex(Buffer** Buffer);
int getBufferInsertedCount(Buffer** Buffer);

int incrementBufferEntryCount(Buffer** Buffer);
int decrementBufferEntryCount(Buffer** Buffer);
void setBufferHeadIndex(Buffer** Buffer, int head);
void setBufferTailIndex(Buffer** Buffer, int tail);
void incrementBufferInsertedCount(Buffer** Buffer);
/* ------------------------------------------------------------ */

/* --------------------- Buffer Helpers ---------------------- */

void printLimitedBufferStatus(Buffer** Buffer);
void printFullBufferStatus(Buffer** Buffer);

/* ------------------------------------------------------------ */