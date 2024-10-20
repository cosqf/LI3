#include <users.h>
#include <glib.h>

#ifndef _USERMANAGER_H_
#define _USERMANAGER_H_

typedef struct userManager UserManager;

void insertUserHash (UserManager *u_mngr, int key, User *User);

UserManager* initializeHashUser ();

void freeHashUser (UserManager* u_mngr);

User* lookupUserHash (UserManager *u_mngr, int id);

GHashTable* getUserTable (UserManager *u_mngr);

#endif