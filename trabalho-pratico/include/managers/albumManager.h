#include <album.h>
#include <output_handling/errorfiles.h>

typedef struct hashtableManager hashtableManager;

#ifndef _ALBUMMANAGER_H_
#define _ALBUMMANAGER_H_

typedef struct albumManager AlbumManager;

void insertAlbumHash (AlbumManager *a_mngr, int key, Album *album);

AlbumManager* initializeHashAlbum ();

void freeHashAlbum (AlbumManager* a_mngr);

bool isAlbumInHash (AlbumManager *a_mngr, int id);

int getDataAlbum (char* path, hashtableManager* mngr);

void callbackAlbum(char** tokens, void* manager, Output* output);
#endif