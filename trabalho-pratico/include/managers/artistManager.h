#include <artists.h>

#ifndef _ARTISTMANAGER_H_
#define _ARTISTMANAGER_H_

typedef struct artistManager ArtistManager;

void insertArtistHash (ArtistManager *a_mngr, int key, Artist *artist);

ArtistManager* initializeHashArtist ();

void freeHashArtist (ArtistManager* a_mngr);

Artist* lookupArtistHash (ArtistManager *a_mngr, int id);
#endif