#include <users.h>
#ifndef _PROCESSINPUT_H_
#define _PROCESSINPUT_H_

#define DEFAULT 1000
typedef enum dataType {Users = 1, Artists, Music} DataType;

typedef struct cmd {
    int query;     // 1, 2, or 3
    int id;         // user ID
    int topN;       // top N lugares
    char *paises;   // (requires memory allocation)
    int ageMin;     // minimum age
    int ageMax;     // maximum age
} CMD;

CMD* getCommand(char* , CMD* );

User* parseDataU (char *, User *);

void parseDataA (char *);

void parseDataM (char *);

Date parseDate(char*);

int* parseIDs(char *, User *);

void getData (char *, DataType );

char * trimString (char *);

#endif  
