#include <users.h>
#include <artists.h>
#include <musics.h>
#include <stdlib.h>
#include "output_handling/outputWriter.h"

#ifndef _ERRORFILES_H_
#define _ERRORFILES_H_

Output* openErrorOutputUser ();

Output* openErrorOutputArtists ();

Output* openErrorOutputMusics ();



void insertErrorFileUser(UserString *user, Output* output);

void insertErrorFileArtists(ArtistString *artist, Output* output);

void insertErrorFileMusics(MusicString *music, Output* output);

#endif