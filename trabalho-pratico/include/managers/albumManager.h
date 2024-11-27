#include <album.h>
#ifndef _ALBUMMANAGER_H_
#define _ALBUMMANAGER_H_

typedef struct albumManager AlbumManager;

void insertAlbumHash (AlbumManager *a_mngr, int key, Album *album);

void freeHashAlbum (AlbumManager* a_mngr);

bool isAlbumInHash (AlbumManager *a_mngr, int id);

void getDataAlbum (char *path, AlbumManager* mngr);

void callbackAlbum(char **tokens, void *manager, Output *output);

#endif