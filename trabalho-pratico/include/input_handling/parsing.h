#include <users.h>

#include <hashtableManager.h>
#include <userManager.h>
#include <musicManager.h>
#include <artistManager.h>


#ifndef _PARSING_H_
#define _PARSING_H_

/**
 * @brief Extracts data from multiple datasets.
 * 
 * This function serves as the main entry point for loading data, delegating specific tasks to other "getData*" functions.
 *  
 * @param path A string containing the path to the folder holding the datasets.
 * @param mngr A pointer to the main manager responsible for all the other datatypes managers.
 * 
 * @return An @c int indicating whether an error occurred during data extraction (0 for success, 1 for error).
 */
int getData (char *path, hashtableManager *mngr);

/**
 * @brief Parses a file and processes each line using a callback function.
 * 
 * This function opens a specified file, skips the header, tokenizes each line based on the delimeter ';', 
 * and processes it using a provided callback function. It is designed to handle generic file parsing 
 * tasks where each line represents structured data to be processed.  
 *  
 * @param pathToFile A string containing the path to the input file.
 * @param processLine A callback function used to process each line. It receives tokens, a manager, and output as arguments.
 * @param manager A pointer to a data structure for managing the parsed data.
 * @param output A pointer to an output structure used for storing results.
 * 
 * @return An @c int indicating success or failure (0 for success, 1 for error).
 */
int parseFile (char* pathToFile, void (processLine)(char**, void*, Output*), void* manager, Output* output);

/**
 * @brief Parses a line according to a separator into tokens.
 * 
 * @param line The string to be tokenized.
 * @param tokens An array of strings where each token will be stored.
 * @param separator The separator to use.
 * 
 * @return The number of tokens parsed.
 */
int parseLine(char* line, char* tokens[], const char* separator);

/**
 * @brief Parses a file with the commands.
 * 
 * This function opens a specified file and tokenizes and processes each line. 

 * @param pathToFile A string containing the path to the file with the commands.
 * @param manager A pointer to a data structure for managing the parsed data.
 * 
 * @return An @c int indicating how many lines it has read. If it returns '-1', is because
 * an error occurred.
 */
int parseCmdFile (char* pathToFile, void* manager);

/**
 * @brief Parses a command line into tokens.
 * 
 * This function tokenizes a given line using spaces as delimeters.
 * Quotation marks (`"`) are treated as group delimiters, preserving all text within them as a single token.  
 * Leading and trailing whitespace is ignored, and each token is null-terminated.  
 *  
 * @param line The input string to be tokenized. The string is modified during parsing.
 * @param tokens An array of strings where pointers to each token will be stored.

 * @return The number of tokens parsed.
 */
int parseCmdLine(char* line, char* tokens[]);

/**
 * @brief Creates a complete file path based on a specified data type.
 * 
 * This function appends the appropriate filename, based on the given data type, to the provided folder path.
 * @param path A string containing the path to the folder holding the datasets.
 * @param type An enum value specifying the data type, which determines the filename to append.  

 * @return A dynamically allocated string containing the full path to the specified dataset file.  
 *         Exits the program if an invalid data type is provided.
 */
char * changePath(char *path, DataType type);

#endif