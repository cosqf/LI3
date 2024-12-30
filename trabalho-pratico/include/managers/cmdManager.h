#include <cmd.h>
#ifndef _CMDMANAGER_H_
#define _CMDMANAGER_H_

/**
 * @brief Structure representing a command manager.
 * It consists of an array of command structs, as well as a counter counting the number of commands.
 */
typedef struct cmdmanager cmdManager;

/**
 * @brief Allocates memory to the cmd Manager, sets the @c CMD array as NULL and sets the counter to 0.
 *
 * @return A pointer to the initialized CMD manager.
 */
cmdManager* createCmdManager ();

/**
 * @brief Creates a @c CMD from tokens and adds it to the cmdManager.
 * If an error happens during the creation of the @c CMD it'll skip the insertion.
 * 
 * @param tokens An array of tokens used to create a @c CMD struct.
 * @param numberTokens The number of tokens the string has.
 * @param manager A pointer to the CMD Manager, where the @c CMD will be stored.
 */
void processCmdLine (char** tokens, int numberTokens, cmdManager* manager);

/**
 * @brief Returns how many commands are stored in the @c CMD manager.
 * 
 * @param mngr A pointer to the CMD Manager.
 * 
 * @return The number of commands in the CMD Manager.
 */
int getCommandsCounter (cmdManager *mngr);

/**
 * @brief Returns a @c CMD, given its index in an array.
 * 
 * @param mngr A pointer to the CMD Manager
 * @param i The index to a specific @c CMD we want to get.
 * 
 * @return A pointer to a command struct.
 */
CMD* getCommandFromMngr (cmdManager *mngr, int i);

/**
 * @brief Frees every command stored and then the CMD manager itself.
 * 
 * @param mngr A pointer to the CMD Manager.
 */
void freeCmdManager (cmdManager *mngr);
#endif