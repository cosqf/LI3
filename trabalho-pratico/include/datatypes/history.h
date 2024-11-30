#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <parsingUtils.h>

#ifndef _HISTORY_H_
#define _HISTORY_H_

typedef struct history History;
typedef struct historyString HistoryString;

History* createHistory (char** tokens);

void deleteHistory (History* history);

HistoryString* createHistoryString (char** tokens);

void deleteHistoryString (HistoryString* history);


// GETTERs

int getHistoryId (History* history);
int getHistoryUserId (History* history);
int getHistoryMusicId (History* history);
Timestamp getHistoryTimestamp (History* history);
Duration getHistoryDuration (History* history);
History* getNextHistory (History* history);

char* getHistoryIdString (HistoryString* history);
char* getHistoryUserIdString (HistoryString* history);
char* getHistoryMusicIdString (HistoryString* history);
char* getHistoryTimestampString (HistoryString* history);
char* getHistoryDurationString (HistoryString* history);
char* getHistoryPlatformString (HistoryString* history);


// SETTERs

History* setNextHistory (History* newNext, History* history);

#endif