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

AlmightyManager* initializeManagers () {
    AlmightyManager *mngr = malloc (sizeof (AlmightyManager));
    mngr->artist = initializeArtistManager();
    mngr->user = initializeUserManager();
    mngr->music = initializeMusicManager();
    mngr->album = initializeAlbumManager();
    mngr->history = initializeHistoryManager();
    return mngr;
}

void freeAlmightyManager (AlmightyManager *mngr) {
    if (mngr->artist) freeArtistManager (mngr->artist);
    if (mngr->user) freeUserManager (mngr->user);
    if (mngr->music) freeMusicManager (mngr->music);
    if (mngr->album) freeAlbumManager (mngr->album);
    if (mngr->history) freeHistoryManager (mngr->history);
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

