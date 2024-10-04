#include <users.h>
#ifndef _GETDATA_H_
#define _GETDATA_H_

void getData (char *path);
void getDataUser (char *);
void getDataArtist (char *);
void getDataMusic (char *);
void freeUser(User *);
void freeArtist(Artist *);

#endif