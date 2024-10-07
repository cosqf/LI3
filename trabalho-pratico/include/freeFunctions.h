#include <users.h>
#include <musics.h>
#include <artists.h>
#include <processInput.h>
#include <stdlib.h>

#ifndef _FREEFUNCTIONS_H_
#define _FREEFUNCTIONS_H_


void freeCmd (CMD *cmd);

void freeUser(User *user);

void freeMusic (Music *music);

#endif