#include <parsingUtils.h>
#include <cmd.h>
#include <userManager.h>
#include <artistManager.h>
#include <users.h>

#ifndef _QUERY1_H_
#define _QUERY1_H_

void query1(CMD*, hashtableManager* mngr, int);

void userinfo (CMD* cmd, User* user, Output* file);

void artistinfo (CMD* cmd, hashtableManager* mngr, Artist* artist, Output* file);

int individualAlbums (hashtableManager* mngr, Artist* artist);

double totalRecipe (hashtableManager* mngr, Artist* artist);

#endif  
