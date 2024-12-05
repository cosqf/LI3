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

bool artistParticipation (ArtistManager* a_mngr, const int* ids, int artistID, int length);

double collectiveArtist (GHashTable* hashtable, Artist* artist, hashtableManager* mngr);

double artistRecipe (int reproductions, double recipe_per_stream);

double participationRecipe (int reproductions, double recipe_per_stream, int constituents);

#endif  
