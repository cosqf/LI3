#include <stdio.h>

#ifndef _PRINCIPAL_H_
#define _PRINCIPAL_H_

/**
 * @brief Runs the main program.
 * Fetches the data, runs the queries and frees the data.
 * 
 * @param pathData String with the path to the datasets.
 * @param pathCmd String with the path to the commands.
 * @return 0 if the program was a success or 1 if an error occured. 
 */
int principal (char* pathData, char* pathCmd);

#endif