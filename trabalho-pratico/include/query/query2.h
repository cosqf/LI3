#include <stdbool.h>
#include <parsingCmd.h>
#include <musics.h>
#include <entityManager.h>

#ifndef _QUERY2_H_
#define _QUERY2_H_

typedef struct {
    int key;
    int duration;
} Tuple;

void query2(CMD *cmd, EntityManager* mngr);

void getArtistsDiscography (int* id, int count, GHashTable* newtable, int duration, char* country, ArtistManager *a_mngr);

void updateDurationHash (int id, GHashTable* newtable, int duration) ;

bool checkIfAlreadyInHashTable (int id, GHashTable* newtable);

int durationInSeconds (Duration time);

Duration secondsInDuration (int seconds);

void feeder(gpointer value, gpointer user_data);

int compareTuple(const void* a, const void* b);

Tuple* sortHash (GHashTable* hash);

#endif  