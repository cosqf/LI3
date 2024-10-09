#include <users.h>
#include <musics.h>
#include <artists.h>
#include <parsingUtils.h>
#include <stdlib.h>
#include <parsingCmd.h>

#ifndef _FREEFUNCTIONS_H_
#define _FREEFUNCTIONS_H_


void freeCmd (CMD *cmd);

void freeUser(User *user);

void freeArtist(Artist *artist);

void freeMusic (Music *music);

void freeUserRaw (UserRaw *user);

void freeArtistRaw (ArtistRaw *artist);

void freeMusicRaw (MusicRaw *music);

#endif