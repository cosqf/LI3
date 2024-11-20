#include <glib.h>
#include <stdlib.h>
#include <stdio.h>
#include <userManager.h>
#include <artistManager.h>
#include <musicManager.h>

#ifndef HASHTABLE_MANAGER_H 
#define HASHTABLE_MANAGER_H

typedef struct hashtableManager hashtableManager;

hashtableManager* initializeHash ();

void freeHash (hashtableManager *mngr);

UserManager* getUserManager (hashtableManager *mngr);
MusicManager* getMusicManager (hashtableManager *mngr);
ArtistManager* getArtistManager (hashtableManager *mngr);
#endif