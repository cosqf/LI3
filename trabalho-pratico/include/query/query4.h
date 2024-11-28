#include <hashtableManager.h>
#include <cmd.h>

#ifndef _QUERY4_H_
#define _QUERY4_H_


void query4 (CMD* cmd, hashtableManager* mngr);

typedef struct {
    Tuple* artistsIds;
    int count;
} ArtistList;


#endif