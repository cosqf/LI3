#include <stdio.h>

#include <users.h>
#include <musics.h>
#include <artists.h>

#ifndef _VALIDATEDATATYPES_H_
#define _VALIDATEDATATYPES_H_

//USERS
bool validUser(User*);

bool validEmail(char*);

bool validBirthdate(char*);

bool validSubscription(char*);

bool validLikes(int*, int);

//MUSICS
bool validMusic(Music*);

bool validDuration(Duration);

bool validArtistId(int*, int);    

//ARTISTS
bool validArtist(Artist*);

bool validIdConst(char*, int);

#endif  
