#include <stdbool.h>
#include <parsingCmd.h>
#include <hashtable.h>
#include <musics.h>

#ifndef _QUERY2_H_
#define _QUERY2_H_

void query2(CMD *cmd);

void insertArtistsHash (int* id, int count, GHashTable* newtable, int duration, char* country);

void updateDurationHash (int id, GHashTable* newtable, int duration) ;

bool checkIfAlreadyInHashTable (int id, GHashTable* newtable);

int durationInSeconds (Duration time);

Duration secondsInDuration (int seconds);

#endif  