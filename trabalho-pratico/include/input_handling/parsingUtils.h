#ifndef _PARSINGUTILS_H_
#define _PARSINGUTILS_H_

#define DEFAULT 2000
typedef enum {Users = 1, Artists, Musics, Historys, Albums} DataType;

typedef struct {
    int year;    //aaaa (<=2024)
    int month;   //mm   (01-12)
    int day;     //dd   (01-31)
    short int error; 
} Date;

typedef struct {
    int hours;     //hh (00-99)
    int minutes;   //mm (00-59)
    int seconds;   //ss (00-59)
    short int error; 
} Duration;

typedef struct timestamp {
    Date date;
    Duration hour;
} Timestamp;

Timestamp parseTimestamp (char* string);

Date parseDate(char*);

Duration parseDuration(char*);

int* parseIDs(char *);

char* trimString (char *);

int IdCounter (char*);

#endif  
