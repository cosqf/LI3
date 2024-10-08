#include <stdio.h>
#include <users.h>
#include <musics.h>

#ifndef _VALIDATION_H_
#define _VALIDATION_H_

Duration parseDuration(char*);

void insertErrorFileUser (UserRaw *user);

void insertErrorFileMusics ();

void insertErrorFileArtists ();

#endif