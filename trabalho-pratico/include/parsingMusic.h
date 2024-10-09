#include <musics.h>

#ifndef _PARSINGMUSIC_H_
#define _PARSINGMUSIC_H_

 
 // fetches data from the music file
MusicRaw* fetchDataM (char *str, MusicRaw *music);


// Parses music
Music* parseDataM (Music *music, MusicRaw *raw); 
#endif