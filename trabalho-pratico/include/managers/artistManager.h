#include <artists.h>
#include <glib.h>
#include <output_handling/errorfiles.h>

#ifndef _ARTISTMANAGER_H_
#define _ARTISTMANAGER_H_

typedef struct artistManager ArtistManager;

void insertArtistHash (ArtistManager *a_mngr, int key, Artist *artist);

ArtistManager* initializeHashArtist ();

void freeHashArtist (ArtistManager* a_mngr);

Artist* lookupArtistHash (ArtistManager *a_mngr, int id);

bool isArtistInHash (ArtistManager *a_mngr, int id);

char* lookupArtistCountryHash (ArtistManager *a_mngr, int id);

void getDataArtist (char *path, ArtistManager* mngr);

void callbackArtist(char **tokens, void *manager, Output *output);

#endif