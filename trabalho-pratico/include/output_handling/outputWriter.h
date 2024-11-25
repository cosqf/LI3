#include <stdio.h>
#include <stdlib.h>
#include <parsingUtils.h>

#ifndef _OUTPUTWRITER_H_
#define _OUTPUTWRITER_H_


typedef struct output Output;

Output* openOutputFile (char* path);

void closeOutputFile (Output* output);

void setOutput (Output* output, char** lines, int counter);

void writeQuerys (Output* output, CMD* cmd);

void writeErrorFile (Output* output);

void writeErrorFileHandle (Output* output, DataType type);

void writeNewLine(Output* output);

#endif