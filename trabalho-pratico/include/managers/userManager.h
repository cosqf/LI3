#include <users.h>
#include <glib.h>
#include <output_handling/errorfiles.h>
#include <historyManager.h>
#include <musicManager.h>

typedef struct almightyManager AlmightyManager;

#ifndef _USERMANAGER_H_
#define _USERMANAGER_H_

/**
 * @brief Structure representing a user manager.
 */
typedef struct userManager UserManager;

/**
 * @brief Inserts a @c User into the hash table.
 *
 * @param u_mngr Pointer to the user manager, where the hash table is stored.
 * @param key The key used to store the user record.
 * @param User Pointer to the user record to be stored.
 */
void insertUserHash (UserManager *u_mngr, int key, User *User);

/**
 * @brief Allocates memory and initializes the user hash table, exiting the program if it fails.
 *
 * @return A pointer to the initialized user manager, where the hash table is stored.
 */
UserManager* initializeHashUser ();

/**
 * @brief Deletes all the contents of the user hash table and frees the pointer to the user manager.
 *
 * @param u_mngr Pointer to the user manager.
 */
void freeHashUser (UserManager* u_mngr);

/**
 * @brief Looks up a user record in the hash table by ID.
 *
 * @param u_mngr Pointer to the user manager.
 * @param id The key to perform the lookup with.
 *
 * @return Pointer to the User record if found, or NULL if not found.
 */
User* lookupUserHash (UserManager *u_mngr, int id);




GHashTable* getUserTable (UserManager *u_mngr);



/**
 * @brief Parses user dataset and checks for validity, writing to error logs if it fails.
 *
 * @param path A string with the path to the user dataset.
 * @param mngr Pointer to the manager containing the user data.
 *
 * @return Returns 1 for error, 0 for success.
 */
int getDataUser (char* path, AlmightyManager* mngr);

/**
 * @brief Callback function used during user parsing.
 * Checks if the tokens received during parsing create a valid user record.
 * Valid entries are added to the hash table; invalid ones go to error logs.
 *
 * @param tokens An array of strings with the tokens to be used.
 * @param manager The user manager.
 * @param output The error file structure.
 */
void callbackUser(char **tokens, void *manager, Output *output);

bool userMatrixIsInitialized (UserManager* mngr);

void createMatrix(HistoryManager* h_mngr, MusicManager* m_mngr, UserManager* u_mngr);

void fillUserIDArray(UserManager* u_mngr);

void updateMatrix (gpointer key, gpointer value, gpointer data);

void freeMatrix(int** matrix, int rows);

void freeUserArray(char** array, int rows);

void processHistory (int** matrix, gpointer value, int line, MusicManager* m_mngr);

void recomendations(char* targetID, char* genre_array[10], int lines_used, int noUsers, UserManager* u_mngr, char*** recUsers);

int getUserMatrixLinesAvail (UserManager *u_mngr);

int getUserMatrixLinesUsed (UserManager *u_mngr);

#endif