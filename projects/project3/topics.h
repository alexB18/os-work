#ifndef URLSIZE
#define URLSIZE 256
#endif

#ifndef CAPSIZE
#define CAPSIZE 512
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
void setEntryTimeStamp(TopicEntry** Entry, struct timeval* newTimeStamp);
void setEntryNum(TopicEntry** Entry, int newEntryNum);
void setEntryPubID(TopicEntry** Entry, int newPubID);
void setEntryPhotoURL(TopicEntry** Entry, char** newPhotoURL);
void setEntryPhotoCaption(TopicEntry** Entry, char** newPhotoCaption);

void initializeEntry(TopicEntry** Entry, int newEntryNum, int newPubID);
void freeEntry(TopicEntry** Entry);
/* -------------------------------------------------- */

/* --------------- TopicEntry Getters --------------- */
struct timeval getEntryTimeStamp(TopicEntry** Entry);
int getEntryNum(TopicEntry** Entry);
int getEntryPubID(TopicEntry** Entry);
char* getEntryPhotoURL(TopicEntry** Entry);
char* getEntryPhotoCaption(TopicEntry** Entry);
/* -------------------------------------------------- */

/* --------------- TopicEntry Helpers --------------- */
void printEntryStatus(TopicEntry** Entry);
/* -------------------------------------------------- */