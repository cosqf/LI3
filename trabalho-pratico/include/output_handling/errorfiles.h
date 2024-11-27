#include <users.h>
#include <artists.h>
#include <musics.h>
#include <history.h>
#include <album.h>
#include <stdlib.h>
#include "output_handling/outputWriter.h"

#ifndef _ERRORFILES_H_
#define _ERRORFILES_H_

Output* openErrorOutputUser ();

Output* openErrorOutputArtists ();

Output* openErrorOutputMusics ();

Output* openErrorOutputHistory ();

Output* openErrorOutputAlbum ();


void insertErrorFileUser(UserString *user, Output* output);

void insertErrorFileArtists(ArtistString *artist, Output* output);

void insertErrorFileMusics(MusicString *music, Output* output);

void insertErrorFileHistory(HistoryString *historyS, Output* output);

void insertErrorFileAlbum(AlbumString *albumS, Output* output);

#endif