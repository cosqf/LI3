#include <stdio.h>
#include <time.h>
#include <stdbool.h>

int principal (char* pathData, char* pathCmd); // argv[1]: path to data, argv[2]: cmd

int tests (char* pathData, char* pathCmd);

void test_principal (char* pathData, char* pathCmd); // same as principal, but with time counters and output comparison

int compareFiles(char* output, char* expected, int queryn);