#include <users.h>

#include <hashtableManager.h>
#include <userManager.h>
#include <musicManager.h>
#include <artistManager.h>


#ifndef _PARSING_H_
#define _PARSING_H_

void getData (char *path, hashtableManager *mngr);

void parseFile (char* pathToFile, void (processLine)(char**, void*, Output*), void* manager, Output* output);

int parseLine(char* line, char* tokens[], const char* separator);

int parseCmdFile (char* pathToFile, void* manager);

int parseCmdLine(char* line, char* tokens[]);

char * changePath(char *path, DataType type);

#endif