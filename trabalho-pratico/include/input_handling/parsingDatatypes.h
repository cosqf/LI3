#include <artists.h>
#include <musics.h>
#include <users.h>

#ifndef _PARSINGDATATYPES_H_
#define _PARSINGDATATYPES_H_


User * fetchDataU (char *str, User *user);

Artist* fetchDataA (char *str, Artist *artist);

Music* fetchDataM (char *str, Music *music);

#endif