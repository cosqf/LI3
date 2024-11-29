#include <hashtableManager.h>
#include <parsingUtils.h>
#include <userManager.h>
#include <artistManager.h>
#include <musicManager.h>
#include <albumManager.h>
#include <historyManager.h>
#include <stdbool.h>

typedef struct hashtableManager {
    UserManager* user;
    ArtistManager* artist;
    MusicManager* music;
    AlbumManager* album;
    HistoryManager* history;
} hashtableManager;

hashtableManager* initializeHash () {
    hashtableManager *mngr = malloc (sizeof (hashtableManager));
    mngr->artist = initializeHashArtist();
    mngr->user = initializeHashUser();
    mngr->music = initializeHashMusic();
    mngr->album = initializeHashAlbum();
    mngr->history = initializeHashHistory();
    return mngr;
}

void freeHash (hashtableManager *mngr) {
    if (mngr->artist) freeHashArtist (mngr->artist);
    if (mngr->user) freeHashUser (mngr->user);
    if (mngr->music) freeHashMusic (mngr->music);
    if (mngr->album) freeHashAlbum (mngr->album);
    if (mngr->history) freeHistory (mngr->history);
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

AlbumManager* getAlbumManager (hashtableManager *mngr) {
    return mngr->album;
}

HistoryManager* getHistoryManager (hashtableManager *mngr) {
    return mngr->history;
}

