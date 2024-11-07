#include <users.h>
#include <artists.h>
#include <musics.h>
#include <stdlib.h>

#ifndef _VALIDATION_H_
#define _VALIDATION_H_

FILE * openErrorFileUser ();

FILE * openErrorFileArtists ();

FILE * openErrorFileMusics ();



FILE * openResultsFileMusics ();

FILE * openResultFileArtists ();

FILE * openResultFileUsers ();

Duration parseDuration(char*);


// for debug
void insertErrorFileUser (UserString *user, FILE *fp);

void insertErrorFileMusics (MusicString *music, FILE *fp);

void insertErrorFileArtists (ArtistString *artist, FILE *fp);

#endif