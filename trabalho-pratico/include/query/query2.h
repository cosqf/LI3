#include <stdbool.h>
#include <cmd.h>
#include <musics.h>
#include <hashtableManager.h>
#include "output_handling/outputWriter.h"

#ifndef _QUERY2_H_
#define _QUERY2_H_

void query2(CMD *cmd, hashtableManager* mngr, int cmdCounter);

void getArtistsDiscography (int id, GHashTable* newtable, int duration, char* country, ArtistManager *a_mngr, Tuple* top10Sorted, int topN, int* minDuration);

void updateSortedArray(GHashTable* table, int id, Tuple* top10Sorted, int topN, int* minDuration);

int durationInSeconds (Duration time);

Duration secondsInDuration (int seconds);

void feeder(gpointer key, gpointer value, gpointer user_data);

void printResult (CMD* cmd, Artist* artist, Duration dur, Output* output);

#endif  