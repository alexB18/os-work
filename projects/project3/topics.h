#ifndef URLSIZE
#define URLSIZE 256
#endif

#ifndef CAPSIZE
#define CAPSIZE 512
#endif

typedef struct topicEntry{
    int entryNum;
    struct timeval timeStamp;
    int pubID;
    char photoURL[URLSIZE]; // URL to photo
    char photoCaption[CAPSIZE]; // photo caption
} topicEntry;

/* --------------- topicEntry Setters --------------- */
void setEntryTimeStamp(topicEntry** Entry, struct timeval* newTimeStamp);
void setEntryNum(topicEntry** Entry, int newEntryNum);
void setEntryPubID(topicEntry** Entry, int newPubID);
void setEntryPhotoURL(topicEntry** Entry, char** newPhotoURL);
void setEntryPhotoCaption(topicEntry** Entry, char** newPhotoCaption);

void initializeEntry(topicEntry** Entry, int newEntryNum, int newPubID);
/* -------------------------------------------------- */

/* --------------- topicEntry Getters --------------- */
struct timeval getEntryTimeStamp(topicEntry** Entry);
int getEntryNum(topicEntry** Entry);
int getEntryPubID(topicEntry** Entry);
char* getEntryPhotoURL(topicEntry** Entry);
char* getEntryPhotoCaption(topicEntry** Entry);
/* -------------------------------------------------- */

/* --------------- topicEntry Helpers --------------- */
void printEntryStatus(topicEntry** Entry);
/* -------------------------------------------------- */