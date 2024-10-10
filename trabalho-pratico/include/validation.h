#include <users.h>
#include <artists.h>
#include <musics.h>
#include <stdlib.h>

#ifndef _VALIDATION_H_
#define _VALIDATION_H_

FILE * openErrorFileUser ();

FILE * openErrorFileArtists ();

FILE * openErrorFileMusics ();

Duration parseDuration(char*);

void insertErrorFileUser (User *user, FILE *fp);

void insertErrorFileMusics (Music *music, FILE *fp);

void insertErrorFileArtists (Artist *artist, FILE *fp);

#endif