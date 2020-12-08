#include <sys/time.h>
#include <stdbool.h>
#include <pthread.h>

#ifndef TRUE
#define TRUE 1
#endif

#ifndef URLSIZE
#define URLSIZE 256 // URL String length
#endif

#ifndef CAPSIZE
#define CAPSIZE 512 // Caption String length
#endif

#ifndef URLSIZE
#define URLSIZE 256 // URL String length
#endif

#ifndef CAPSIZE
#define CAPSIZE 512 // Caption String length
#endif

#ifndef MAXENTRIES
#define MAXENTRIES 10  // TopicQueue size
#endif

#ifndef MAXNAMESIZE
#define MAXNAMESIZE 1024
#endif

typedef struct topicEntry{
    int entryNum;
    struct timeval timeStamp;
    int pubID;
    char* photoURL; // URL to photo
    char* photoCaption; // photo caption
} Entry;

typedef struct TopicQueue {
    bool isFull;
    int entryCount, head, tail, highestEntryNum, id, size;
    char name[MAXNAMESIZE];
    struct topicEntry** entries;
    pthread_mutex_t lock;
} TopicQueue;

/* --------------- Entry Constructor/Destructor --------------- */
Entry* constructEntry();
void initializeEntry(Entry** Entry);
void destroyEntry(Entry** Entry);
void resetEntry(Entry** Entry);

/* ------------------------------------------------------------ */


/* --------------- Entry Setters --------------- */
void setEntryTimeStamp(Entry** Entry, struct timeval* newTimeStamp);
void setEntryNum(Entry** Entry, int newEntryNum);
void setEntryPubID(Entry** Entry, int newPubID);
void setEntryPhotoURL(Entry** Entry, char** newPhotoURL);
void setEntryPhotoCaption(Entry** Entry, char** newPhotoCaption);
/* -------------------------------------------------- */

/* --------------- Entry Getters --------------- */
struct timeval getEntryTimeStamp(Entry** Entry);
int getEntryNum(Entry** Entry);
int getEntryPubID(Entry** Entry);
char* getEntryPhotoURL(Entry** Entry);
char* getEntryPhotoCaption(Entry** Entry);
/* -------------------------------------------------- */

/* --------------- Entry Helpers --------------- */
void printEntryStatus(Entry** Entry);
/* -------------------------------------------------- */

/* --------------- TopicQueue Constructor/Destructor -------------- */
TopicQueue* constructTopicQueue(int id, char* topicName, int size);
void initializeTopicQueue(TopicQueue** TopicQueue);
void destroyTopicQueue(TopicQueue** TopicQueue);
/* ------------------------------------------------------------ */

int enqueue(TopicQueue** TopicQueue, Entry** Entry);
int getEntry(TopicQueue** TopicQueue, int lastEntry, Entry** emptyEntry);
int dequeue(TopicQueue** TopicQueue, suseconds_t delta);

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