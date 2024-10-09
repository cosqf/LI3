#include <users.h>
#ifndef _PARSINGUTILS_H_
#define _PARSINGUTILS_H_

#define DEFAULT 2000
typedef enum {Users = 1, Artists, Musics} DataType;


Date parseDate(char*);

int* parseIDs(char *, void*, DataType);

char * trimString (char *);

void updateCount(void*, DataType, int);

#endif  
