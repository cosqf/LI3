#include <hashtableManager.h>
#include <parsingUtils.h>
#include <userManager.h>
#include <artistManager.h>
#include <musicManager.h>
#include <stdbool.h>

typedef struct hashtableManager {
    UserManager* user;
    ArtistManager* artist;
    MusicManager* music;
} hashtableManager;

hashtableManager* initializeHash () {
    hashtableManager *mngr = malloc (sizeof (hashtableManager));
    mngr->artist = initializeHashArtist();
    mngr->user = initializeHashUser();
    mngr->music = initializeHashMusic();
    return mngr;
}

void freeHash (hashtableManager *mngr) {
    if (mngr->artist) freeHashArtist (mngr->artist);
    if (mngr->user) freeHashUser (mngr->user);
    if (mngr->music) freeHashMusic (mngr->music);
    free (mngr);
}

UserManager* getUserManager (hashtableManager *mngr) {
    return mngr->user;
}

MusicManager* getMusicManager (hashtableManager *mngr) {
    return mngr->music;
}

ArtistManager* getArtistManager (hashtableManager *mngr) {
    return mngr->artist;
}

bool checkIfAlreadyInHashTable (int key, GHashTable* table) {
    if (g_hash_table_lookup (table, GINT_TO_POINTER(key)) == NULL) return false;
    else return true;
}