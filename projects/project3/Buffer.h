#include <sys/time.h>
#include "Entry.h"

#ifndef BUFFERSIZE
#define BUFFERSIZE 256  // buffer size
#endif

typedef struct Buffer {
    int count, head, tail, inserted;
    struct Entry** entries;
} Buffer;

/* --------------- Buffer Constructor/Destructor -------------- */
void initializeBuffer(Buffer** Buffer);
void destroyBuffer(Buffer** Buffer);
/* ------------------------------------------------------------ */

/* ------------------ Enqueue/Dequeue methods ----------------- */
/* ------------------------------------------------------------ */