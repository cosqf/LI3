#include <parsingUtils.h>
#include <cmd.h>
#include <userManager.h>
#include <artistManager.h>
#include <musicManager.h>
#include <users.h>

#ifndef _QUERY1_H_
#define _QUERY1_H_

void query1(CMD*, hashtableManager* mngr, int);

void userinfo (CMD* cmd, User* user, Output* file);

void artistinfo (CMD* cmd, hashtableManager* mngr, Artist* artist, Output* file);

int individualAlbums (hashtableManager* mngr, Artist* artist);

double totalRecipe (hashtableManager* mngr, Artist* artist);

double singleArtist (GHashTable* hashtable, Artist* artist, hashtableManager* mngr);

void artistParticipation (ArtistManager* a_mngr, const int* ids, int artistID, int length, int *constituents);

double collectiveArtist (GHashTable* hashtable, Artist* artist, hashtableManager* mngr);

#endif  
