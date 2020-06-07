#ifndef URLSIZE
#define URLSIZE 256
#endif

#ifndef CAPSIZE
#define CAPSIZE 512
#endif

#ifndef MAXENTRIES
#define MAXENTRIES 10
#endif

#ifndef MAXTOPICS
#define MAXTOPICS 5
#endif

typedef struct TopicEntry{
    int entryNum;
    struct timeval timeStamp;
    int pubID;
    char* photoURL; // URL to photo
    char* photoCaption; // photo caption

    // pointer to next TopicEntry in queue
    struct TopicEntry* NextEntry;
} TopicEntry;

/* --------------- TopicEntry Setters --------------- */
void setEntryTimeStamp(TopicEntry* Entry, struct timeval* newTimeStamp);
void setEntryNum(TopicEntry* Entry, int newEntryNum);
void setEntryPubID(TopicEntry* Entry, int newPubID);
void setEntryPhotoURL(TopicEntry* Entry, char** newPhotoURL);
void setEntryPhotoCaption(TopicEntry* Entry, char** newPhotoCaption);

void initializeEntry(TopicEntry** Entry, int newEntryNum, int newPubID);
void freeEntry(TopicEntry* Entry);
/* -------------------------------------------------- */

/* --------------- TopicEntry Getters --------------- */
struct timeval getEntryTimeStamp(TopicEntry* Entry);
int getEntryNum(TopicEntry* Entry);
int getEntryPubID(TopicEntry* Entry);
char* getEntryPhotoURL(TopicEntry* Entry);
char* getEntryPhotoCaption(TopicEntry* Entry);
/* -------------------------------------------------- */

/* --------------- TopicEntry Helpers --------------- */
void printEntryStatus(TopicEntry* Entry);
/* -------------------------------------------------- */

typedef struct TopicQueue{

    // Array containing all address topics
    // Will hold MAXENTRIES and will be used
    // to implement queue
    struct TopicEntry** topicAddressArray;

    struct TopicEntry* head;
    struct TopicEntry* tail;

    int numberOfTopics;


} TopicQueue;

/* --------------- TopicQueue Setters --------------- */
void setTopicQueueHead(TopicQueue* Queue, TopicEntry** NewHead);
void setTopicQueueTail(TopicQueue* Queue, TopicEntry** NewTail);
void incrementNumberOfTopics(TopicQueue* Queue);
/* -------------------------------------------------- */

/* --------------- TopicQueue Getters --------------- */
TopicEntry* getTopicQueueHead(TopicQueue* Queue);
TopicEntry* getTopicQueueTail(TopicQueue* Queue);
int getNumberOfTopics(TopicQueue* Queue);
/* -------------------------------------------------- */

/* --------------- TopicQueue Helpers --------------- */
void initializeTopicQueue(TopicQueue** Queue);
void freeTopicQueue(TopicQueue* Queue);
/* -------------------------------------------------- */