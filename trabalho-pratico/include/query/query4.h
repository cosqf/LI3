#include <hashtableManager.h>
#include <cmd.h>

#ifndef _QUERY4_H_
#define _QUERY4_H_

void query4 (CMD* cmd, HistoryManager* historyManager, MusicManager* musicManager, ArtistManager* artistManager, int cmdCounter);

typedef struct {
    Tuple* artistsIds;
    int count;
} ArtistList;

void freeArtistList (ArtistList* list) ;
#endif