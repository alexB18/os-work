#include <sys/time.h>

#ifndef TRUE
#define TRUE 1
#endif

#ifndef URLSIZE
#define URLSIZE 256 // URL String length
#endif

#ifndef CAPSIZE
#define CAPSIZE 512 // Caption String length
#endif

typedef struct topicEntry{
    int entryNum;
    struct timeval timeStamp;
    int pubID;
    char* photoURL; // URL to photo
    char* photoCaption; // photo caption
} Entry;

/* --------------- Entry Constructor/Destructor --------------- */
void initializeEntry(Entry** Entry);
void destroyEntry(Entry** Entry);

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