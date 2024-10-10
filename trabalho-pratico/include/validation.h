#include <users.h>
#include <artists.h>
#include <musics.h>

#ifndef _VALIDATION_H_
#define _VALIDATION_H_

Duration parseDuration(char*);

void insertErrorFileUser (User *user);

void insertErrorFileMusics ();

void insertErrorFileArtists ();

#endif