#include <musics.h>
#include <glib.h>

#ifndef _MUSICMANAGER_H_
#define _MUSICMANAGER_H_

typedef struct musicManager MusicManager;
void insertMusicHash (MusicManager *a_mngr, int key, Music *Music);

MusicManager* initializeHashMusic ();

void freeHashMusic (MusicManager* a_mngr);

Music* lookupMusicHash (MusicManager *a_mngr, int id);

GHashTable* getMusicTable (MusicManager *m_mngr);

void iterateMusic(MusicManager* m_mngr, void (*MusicProcessor)(gpointer value, gpointer music_data), gpointer music_data);

#endif