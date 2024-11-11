#include <stdio.h>
#include <time.h>
#include <stdbool.h>

#ifndef _TEST_H_
#define _TEST_H_

int tests (char* pathData, char* pathCmd, char* pathOutput);

void test_principal (char* pathData, char* pathCmd, char* pathOutput); // same as principal, but with time counters and output comparison

int compareFiles(char* output, char* expected, int queryn);

#endif