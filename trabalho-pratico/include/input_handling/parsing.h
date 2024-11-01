#include <users.h>

#include <entityManager.h>
#include <userManager.h>
#include <musicManager.h>
#include <artistManager.h>

#ifndef _PARSING_H_
#define _PARSING_H_

void getData (char *path, EntityManager *mngr);

void parseLine(char* line, char* tokens[], const char* separator);

char * changePath(char *path, DataType type);
#endif