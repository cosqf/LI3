#include <stdio.h>
#include <stdlib.h>
#include <parsingUtils.h>
#include <cmd.h>

#ifndef _OUTPUTWRITER_H_
#define _OUTPUTWRITER_H_

/**
 * @brief Structure representing an output manager for handling file output operations.
 */
typedef struct output Output;

/**
 * @brief Allocates memory for an @c Output structure and opens the specified file.
 * 
 * @param path Path to the output file.
 * 
 * @return Pointer to the initialized @c Output structure.
 */
Output* openOutputFile (char* path);

/**
 * @brief Closes the output file and frees the memory allocated for the @c Output structure.
 *
 * @param output Pointer to the @c Output structure to be closed and freed.
 */
void closeOutputFile (Output* output);

/**
 * @brief Sets the lines to be written to the output.

 * @param output Pointer to the Output structure.
 * @param lines Array of strings representing the lines to be written.
 * @param counter Number of lines to be written.
 */
void setOutput (Output* output, char** lines, int counter);

/**
 * @brief Generic function that writes output in the format specified by a command.
 *
 * @param output Pointer to the Output structure.
 * @param cmd Pointer to the CMD structure.
 */
void writeQuerys (Output* output, CMD* cmd);

/**
 * @brief Generic function that writes an error file.

 * @param output Pointer to the Output structure.
 */
void writeErrorFile (Output* output);

/**
 * @brief Writes headers for error files based on the specified data type.

 * @param output Pointer to the Output structure.
 * @param type The data type specifying which headers to write.
 */
void writeErrorFileHandle (Output* output, DataType type);

/**
 * @brief Writes a newline character to the output file.

 * @param output Pointer to the Output structure.
 */
void writeNewLine(Output* output);

#endif