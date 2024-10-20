#include <stdio.h>
#include <time.h>
#include <stdbool.h>

int principal (char** argv); // argv[1]: path to data, argv[2]: cmd

int tests (char** argv);

void test_principal (char** argv); // same as principal, but with time counters and output comparison

int compareFiles(char* output, char* expected, int queryn);