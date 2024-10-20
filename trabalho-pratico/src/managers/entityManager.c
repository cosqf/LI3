#include "entityManager.h"
#include <parsingUtils.h>
#include <userManager.h>
#include <artistManager.h>
#include <musicManager.h>
#include <stdbool.h>

typedef struct entityManager {
    UserManager* user;
    ArtistManager* artist;
    MusicManager* music;
} EntityManager;

EntityManager* initializeHash () {
    EntityManager *mngr = malloc (sizeof (EntityManager));
    mngr->artist = initializeHashArtist();
    mngr->user = initializeHashUser();
    mngr->music = initializeHashMusic();
    return mngr;
}

void freeHash (EntityManager *mngr) {
    freeHashArtist (mngr->artist);
    freeHashUser (mngr->user);
    freeHashMusic (mngr->music);
    free (mngr);
}

UserManager* getUserManager (EntityManager *mngr) {
    return mngr->user;
}

MusicManager* getMusicManager (EntityManager *mngr) {
    return mngr->music;
}

ArtistManager* getArtistManager (EntityManager *mngr) {
    return mngr->artist;
}

bool checkIfAlreadyInHashTable (int key, GHashTable* table) {
    if (g_hash_table_lookup (table, GINT_TO_POINTER(key)) == NULL) return false;
    else return true;
}