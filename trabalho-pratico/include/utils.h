#include <stdio.h>
#include <parsingUtils.h>
#include <stdbool.h>
#include <glib.h>
#include <musics.h>

#ifndef _UTILS_H_
#define _UTILS_H_

FILE* openFile (char * argv);

bool mallocErrorCheck (void* add);

char *trimString(char *str);

char* trimStringWithoutBrackets (char* str);

char** lower (char** line);

int isletter(char);

int isDigit(char);

int isstr(char*, int);

GHashTable* createHash ();

void deleteHash (GHashTable* hash);

void insertHash (GHashTable* hash, int key, int value);

char* durationInString(Duration time);

void writeMusicsToErrorFile(GHashTable* );
void writeUsersToErrorFile(GHashTable* );
void writeArtistsToErrorFile(GHashTable* );

bool convertToInt(const char *str, int *out);

int compareDate(Date dateA, Date dateB);
#endif