#include <stdbool.h>
#include <cmd.h>
#include <musics.h>
#include <hashtableManager.h>
#include "output_handling/outputWriter.h"

#ifndef _QUERY2_H_
#define _QUERY2_H_

void query2(CMD *cmd, hashtableManager* mngr, int cmdCounter);

void getArtistsDiscography (const int* id, int count, GHashTable* newtable, int duration, char* country, ArtistManager *a_mngr);

bool checkIfAlreadyInHashTable (int id, GHashTable* newtable);

int durationInSeconds (Duration time);

Duration secondsInDuration (int seconds);

void feeder(gpointer value, gpointer user_data);

void printResult (CMD* cmd, Artist* artist, Duration dur, Output* output);

char* getPathFileToQuery2 (int i);

#endif  