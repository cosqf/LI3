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
 * @brief A matrix feeder struct.
 */
typedef struct matrixFeeder {
    MusicManager* m_mngr;
    UserManager* u_mngr;
} MatrixFeeder;

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
UserManager* initializeUserManager ();

/**
 * @brief Deletes all the contents of the user hash table and frees the pointer to the user manager.
 *
 * @param u_mngr Pointer to the user manager.
 */
void freeUserManager (UserManager* u_mngr);

/**
 * @brief Looks up a user record in the hash table by ID.
 *
 * @param u_mngr Pointer to the user manager.
 * @param id The key to perform the lookup with.
 *
 * @return Pointer to the User record if found, or NULL if not found.
 */
User* lookupUserHash (UserManager *u_mngr, int id);

/**
 * @brief Iterates through all entries in the user hash table and processes each entry using a callback function.
 *
 * @param u_mngr Pointer to the user manager.
 * @param UserProcessor Callback function to process each user record.
 * @param user_data Pointer to additional data passed to the callback function.
 */
void iterateUser(UserManager* u_mngr, void (*UserProcessor)(gpointer key, gpointer value, gpointer user_data), gpointer user_data);

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

/**
 * @brief Checks if the matrix that contains all the users and the amount of times they have listened to each genre exists.
 *
 * @param u_mngr Pointer to the user manager.
 *
 * @return Returns 1 for success, 0 for error.
 */
bool userMatrixIsInitialized (UserManager* u_mngr);

/**
 * @brief Creates the matrix that contains all the users and the amount of times they have listened to each genre.
 *
 * @param h_mngr Pointer to the history manager.
 * @param m_mngr Pointer to the music manager.
 * @param u_mngr Pointer to the user manager.
 */
void createMatrixAndArray(HistoryManager* h_mngr, MusicManager* m_mngr, UserManager* u_mngr);

/**
 * @brief Iterates the user hashtable, adding each ID to the user array and replacing the hashtable entry with an updated one.
 *
 * @param u_mngr Pointer to the user manager.
 */
void fillUserIDArray(UserManager* u_mngr);

/**
 * @brief Callback function used in traverseHistorybyUser to update the matrix counters.
 * Handles the necessary information to safely call the auxiliary function processHistory and fill the matrix.
 * 
 * @param key The user ID to which the history entry is associated.
 * @param value The first history entry associated to said user.
 * @param data A pointer to a MatrixFeeder.
 */
void updateMatrix (gpointer key, gpointer value, gpointer data);

/**
 * @brief Creates a copy of a given matrix.
 * 
 * @param matrix Pointer to the matrix to copy.
 * @param rows Number of rows in the matrix to copy.
 * @param colums Number of columns in the matrix to copy.
 */
int** copyMatrix(int** matrix, int rows, int columns);

/**
 * @brief Creates a copy of a given user array.
 * 
 * @param array Pointer to the user array to copy.
 * @param slots Number of slots in the user array to copy.
 */
char** copyUserArray (char** array, int slots);

/**
 * @brief Frees each row in the matrix and the matrix pointer itself.
 * 
 * @param matrix A pointer to the matrix.
 * @param rows The number of rows in the matrix.
 */
void freeMatrix(int** matrix, int rows);

/**
 * @brief Frees each slot in the array and the array pointer itself.
 * 
 * @param matrix A pointer to the array.
 * @param slots The number of slots in the array.
 */
void freeUserArray(char** array, int slots);

/**
 * @brief Auxiliary function to updateMatrix, processes a linked list of history entries, updating the counters on the given line in the matrix.
 * 
 * @param matrix A pointer to the matrix.
 * @param value A pointer to a history entry (linked list).
 * @param line The line to update.
 * @param m_mngr Pointer to the music manager.
 */
void processHistory (int** matrix, gpointer value, int line, MusicManager* m_mngr);

/**
 * @brief Calculates user recommendations through a function provided by the professors.
 * Allocates memory for the resulting array, which the caller is responsible for freeing.
 * 
 * @param targetID Formatted target user ID to generate recommendations.
 * @param genre_array An array containing the name of each music genre following the same order as the matrix.
 * @param lines_used The number of lines occupied in the matrix (total number of users).
 * @param noUsers The number of recommendations to calculate.
 * @param u_mngr Pointer to the user manager.
 * @param recUsers Pointer to the array that will store the results.
 */
void recommendations(char* targetID, char* genre_array[10], int lines_used, int noUsers, UserManager* u_mngr, char*** recUsers);

/**
 * @brief A getter function for the number of lines available in the matrix, which is also the number of slots available in the user array.
 *
 * @param u_mngr Pointer to the user manager.
 *
 * @return Returns the number of lines in the matrix.
 */
int getUserMatrixLinesAvail (UserManager *u_mngr);

/**
 * @brief A getter function for the number of lines used in the matrix, which is also the number of slots occupied in the user array.
 *
 * @param u_mngr Pointer to the user manager.
 *
 * @return Returns the number of lines in the matrix that have an associated user.
 */
int getUserMatrixLinesUsed (UserManager *u_mngr);

#endif