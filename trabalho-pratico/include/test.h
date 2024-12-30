#include <stdio.h>
#include <time.h>
#include <stdbool.h>

#ifndef _TEST_H_
#define _TEST_H_

/**
 * @brief Runs the test program.
 * Runs the program and prints the memory usage and how long it took.
 * 
 * @param pathData String with the path to the datasets.
 * @param pathCmd String with the path to the commands.
 * @param pathOutput String with the path where the output will be stored.
 * @return 0 if the program was a success or 1 if an error occured. 
 */
int tests (char* pathData, char* pathCmd, char* pathOutput);

/**
 * @brief Runs the test program with time analyzis.
 * Fetches the data, runs the queries, counting how long each takes,
 * checks for differences in the expected results and actual results and frees the data.
 * 
 * @param pathData String with the path to the datasets.
 * @param pathCmd String with the path to the commands.
 * @param pathOutput String with the path where the output will be stored.
 * @return 0 if the program was a success or 1 if an error occured. 
 */
void test_principal (char* pathData, char* pathCmd, char* pathOutput); // same as principal, but with time counters and output comparison

/**
 * @brief Compares two files.
 * Opens two files and compares them line by line, printing any difference it finds.
 * 
 * @param output String with the path where the output will be stored.
 * @param expected String with the path where the expected results are.
 * @param queryn Number of query for printint purposes.
 */
int compareFiles(char* output, char* expected, int queryn);

#endif