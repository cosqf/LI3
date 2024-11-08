#include <glib.h>
#include <musicManager.h>
#include <musics.h>
#include <artistManager.h>
#include <parsingUtils.h>
#include <parsing.h>
#include <stdlib.h>
#include <utils.h>
#include <errorfiles.h>
#include <validateDatatypes.h>

typedef struct musicManager {
    GHashTable *music;
} MusicManager;

void insertMusicHash (MusicManager *m_mngr, int key, Music *Music) {
    g_hash_table_insert(m_mngr->music, GINT_TO_POINTER (key), Music);
}

MusicManager* initializeHashMusic () {
    MusicManager* m_mngr = malloc (sizeof (MusicManager));
    if (m_mngr == NULL) {
        perror("Failed to allocate memory for MusicManager");
        exit(EXIT_FAILURE); 
    }
    m_mngr->music = g_hash_table_new_full(g_direct_hash, g_direct_equal, NULL, (GDestroyNotify)deleteMusic);
    return m_mngr;
}

void freeHashMusic (MusicManager* m_mngr) {
    g_hash_table_destroy (m_mngr->music);
    free (m_mngr);
}

Music* lookupMusicHash (MusicManager *m_mngr, int id) {
    Music* Music = g_hash_table_lookup (m_mngr->music, GINT_TO_POINTER(id));
    return Music;
}

GHashTable* getMusicTable (MusicManager *m_mngr) {
    return m_mngr->music;
}


void iterateMusic(MusicManager* m_mngr, void (*MusicProcessor)(gpointer value, gpointer music_data), gpointer music_data) {
    GHashTableIter iter;
    gpointer key, value;

    g_hash_table_iter_init(&iter, m_mngr->music);

    while (g_hash_table_iter_next(&iter, &key, &value)) {
        MusicProcessor(value, music_data);
    }
}


void getDataMusic (char *path, hashtableManager* mngr) {
    FILE *errorFileMusic = openErrorFileMusics();

    parseFile(path, callbackMusic, mngr, errorFileMusic);

    fclose(errorFileMusic); 
}

void callbackMusic (char** tokens, void* manager, FILE* errorFile) { // receives entity manager
    hashtableManager* mngr = (hashtableManager*) manager;
    MusicManager* music_mngr = getMusicManager (mngr);
    ArtistManager* artist_mngr = getArtistManager (mngr);

    MusicString* musicS = createMusicString (tokens);
    if (!validMusic(musicS, artist_mngr)) insertErrorFileMusics(musicS, errorFile);
    else {
        Music* music = createMusic (tokens);
        insertMusicHash(music_mngr, getMusicID(music), music);
    }
    deleteMusicString (musicS);
}