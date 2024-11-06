#include <artists.h>
#include <glib.h>

#ifndef _ARTISTMANAGER_H_
#define _ARTISTMANAGER_H_

typedef struct artistManager ArtistManager;

void insertArtistHash (ArtistManager *a_mngr, int key, Artist *artist);

ArtistManager* initializeHashArtist ();

void freeHashArtist (ArtistManager* a_mngr);

Artist* lookupArtistHash (ArtistManager *a_mngr, int id);

GHashTable* getArtistTable (ArtistManager *a_mngr);

void callbackArtist(char **tokens, void *manager, FILE *errorFile);

#endif