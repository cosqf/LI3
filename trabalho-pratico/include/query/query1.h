#include <parsingUtils.h>
#include <cmd.h>
#include <userManager.h>
#include <users.h>

#ifndef _QUERY1_H_
#define _QUERY1_H_

void query1(CMD*, UserManager*, ArtistManager*, int);

void userinfo (CMD* cmd, User* user, Output* file);

void artistinfo (CMD* cmd, Artist* artist, Output* file);

#endif  
