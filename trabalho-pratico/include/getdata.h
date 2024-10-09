#include <users.h>
#ifndef _GETDATA_H_
#define _GETDATA_H_

void getData (char *path);

void getDataUser (char *);

void getDataArtist (char *);

void getDataMusic (char *);

char * changePath(char *path, DataType type);
#endif