#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#ifndef _ALBUM_H_
#define _ALBUM_H_

typedef struct album Album;
typedef struct albumString AlbumString;

Album* createAlbum(char** tokens);

void deleteAlbum (Album* album);

AlbumString* createAlbumString (char** tokens);

void deleteAlbumString (AlbumString* album);


int getAlbumId(Album* album);
char* getAlbumTitle(Album* album);
int* getAlbumArtistId(Album* album);
unsigned int getAlbumArtistIdCount(Album* album);
short int getAlbumYear(Album* album);

char* getAlbumIdString (AlbumString* album);
char* getAlbumTitleString (AlbumString* album);
char* getAlbumArtistIdString (AlbumString* album);
char* getAlbumArtistIdCountString (AlbumString* album);
char* getAlbumYearString (AlbumString* album);
char* getAlbumProducerString (AlbumString* album);

#endif