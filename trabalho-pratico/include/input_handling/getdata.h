#include <users.h>

#include <entityManager.h>
#include <userManager.h>
#include <musicManager.h>
#include <artistManager.h>

#ifndef _GETDATA_H_
#define _GETDATA_H_

void getData (char *path, EntityManager *mngr);

void getDataUser (char *, UserManager *u_mngr, MusicManager *m_mngr);

void getDataArtist (char *, ArtistManager *mngr);

void getDataMusic (char *, MusicManager *m_mngr, ArtistManager *a_mngr);

char * changePath(char *path, DataType type);
#endif