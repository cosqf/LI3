#include <users.h>
#include <musics.h>
#include <artists.h>
#ifndef _PROCESSINPUT_H_
#define _PROCESSINPUT_H_

#define DEFAULT 2000
typedef enum dataType {Users = 1, Artists, Musics} DataType;

typedef struct cmd {
    int query;     // 1, 2, or 3
    int id;         // user ID
    int topN;       // top N places
    char *paises;   // (requires memory allocation)
    int ageMin;     // minimum age
    int ageMax;     // maximum age
} CMD;

CMD* getCommand(char* , CMD* );

User* parseDataU (char *, User *);

Artist* parseDataA (char *, Artist *);

Music* parseDataM (char *, Music *);

Date parseDate(char*);

int* parseIDs(char *, void*, DataType);

char * trimString (char *);

void updateCount(void*, DataType, int);

void freeCmd (CMD *);
#endif  
