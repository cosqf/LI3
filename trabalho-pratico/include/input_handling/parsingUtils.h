#ifndef _PARSINGUTILS_H_
#define _PARSINGUTILS_H_

#define DEFAULT 2000
typedef enum {Users = 1, Artists, Musics} DataType;

typedef struct {
    int year;    //aaaa (<=2024)
    int month;   //mm   (01-12)
    int day;     //dd   (01-31)
    short int error; 
} Date;


Date parseDate(char*);

int* parseIDs(char *, void*, DataType);

char* trimString (char *);

int IdCounter (char*);

#endif  
