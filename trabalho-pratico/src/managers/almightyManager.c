#include <almightyManager.h>
#include <parsingUtils.h>
#include <userManager.h>
#include <artistManager.h>
#include <musicManager.h>
#include <albumManager.h>
#include <historyManager.h>
#include <stdbool.h>

typedef struct almightyManager {
    UserManager* user;
    ArtistManager* artist;
    MusicManager* music;
    AlbumManager* album;
    HistoryManager* history;
} AlmightyManager;

AlmightyManager* initializeHash () {
    AlmightyManager *mngr = malloc (sizeof (AlmightyManager));
    mngr->artist = initializeHashArtist();
    mngr->user = initializeHashUser();
    mngr->music = initializeHashMusic();
    mngr->album = initializeHashAlbum();
    mngr->history = initializeHashHistory();
    return mngr;
}

void freeHash (AlmightyManager *mngr) {
    if (mngr->artist) freeHashArtist (mngr->artist);
    if (mngr->user) freeHashUser (mngr->user);
    if (mngr->music) freeHashMusic (mngr->music);
    if (mngr->album) freeHashAlbum (mngr->album);
    if (mngr->history) freeHistory (mngr->history);
    free (mngr);
}

UserManager* getUserManager (AlmightyManager *mngr) {
    return mngr->user;
}

MusicManager* getMusicManager (AlmightyManager *mngr) {
    return mngr->music;
}

ArtistManager* getArtistManager (AlmightyManager *mngr) {
    return mngr->artist;
}

AlbumManager* getAlbumManager (AlmightyManager *mngr) {
    return mngr->album;
}

HistoryManager* getHistoryManager (AlmightyManager *mngr) {
    return mngr->history;
}

