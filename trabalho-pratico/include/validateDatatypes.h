#include <stdio.h>

#include <users.h>
#include <musics.h>
#include <artists.h>

#include <musicManager.h>
#include <artistManager.h>

#ifndef _VALIDATEDATATYPES_H_
#define _VALIDATEDATATYPES_H_

//USERS
bool validUser(UserString*, MusicManager *);

bool validEmail(char*);

bool validBirthdate(char*);

bool validSubscription(char*);

bool validLikes(int*, int, MusicManager*);

//MUSICS
bool validMusic(MusicString*, ArtistManager*);

bool validDuration(Duration);

bool validArtistId(int*, int, ArtistManager*);    

//ARTISTS
bool validArtist(ArtistString*);

bool validIdConst(char*, int);

//LISTS
bool validList (char*);

#endif  
