#include <stdio.h>
#include <processInput.h>
#ifndef _UTILS_H_
#define _UTILS_H_

FILE* openFile (char * argv);

bool mallocErrorCheck (void* add);

char *trimString(char *str);

void updateCount(void* IDnum, DataType type, int count);
#endif