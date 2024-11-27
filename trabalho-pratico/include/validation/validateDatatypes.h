#include <stdio.h>

#include <users.h>
#include <musics.h>
#include <artists.h>
#include <history.h>

#include <musicManager.h>
#include <artistManager.h>
#include <albumManager.h>

#ifndef _VALIDATEDATATYPES_H_
#define _VALIDATEDATATYPES_H_

//USERS
bool validUser(UserString*, MusicManager *);

bool validEmail(char*);

bool validBirthdate(char*);

bool validSubscription(char*);

bool validLikes(const int*, int, MusicManager*);

//MUSICS
bool validMusic(MusicString*, ArtistManager*, AlbumManager*);

bool validDuration(Duration);

bool validAlbumID(int, AlbumManager*);

//ARTISTS
bool validArtist(ArtistString*);

bool validIdConst(char*, int);

bool validType(char*);

//LISTS
bool validList (char*);

bool validArtistId(int*, int, ArtistManager*);

//HISTORY
bool validHistory(HistoryString*);

bool validPlatform(char*);

//ALBUMS
bool validAlbum(AlbumString* album, AlbumManager* al_mngr, ArtistManager* a_mngr);

#endif  
