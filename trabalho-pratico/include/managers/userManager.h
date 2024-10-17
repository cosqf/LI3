#include <users.h>
#include <glib.h>

#ifndef _USERMANAGER_H_
#define _USERMANAGER_H_

typedef struct userManager UserManager;

void insertUserHash (UserManager *a_mngr, int key, User *User);

UserManager* initializeHashUser ();

void freeHashUser (UserManager* a_mngr);

User* lookupUserHash (UserManager *a_mngr, int id);

GHashTable* getUserTable (UserManager *u_mngr);
#endif