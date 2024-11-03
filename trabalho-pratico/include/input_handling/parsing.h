#include <users.h>

#include <entityManager.h>
#include <userManager.h>
#include <musicManager.h>
#include <artistManager.h>


#ifndef _PARSING_H_
#define _PARSING_H_

void getData (char *path, EntityManager *mngr);

int parseLine(char* line, char* tokens[], const char* separator);

int parseCmdLine(char* line, char* tokens[]);

char * changePath(char *path, DataType type);
#endif