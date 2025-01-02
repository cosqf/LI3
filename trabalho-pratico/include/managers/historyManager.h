#include <history.h>
#include <queryUtils.h>
#include <musicManager.h>
#include "output_handling/outputWriter.h"

#ifndef _HISTORYMANAGER_H_
#define _HISTORYMANAGER_H_

/**
 * @brief Structure representing a history manager.
 */
typedef struct historyManager HistoryManager;


// Hash

/**
 * @brief Allocates memory and initializes the history hash table, exiting the program if it fails.
 *
 * @return A pointer to the initialized history manager, where the History hash table is stored.
 */
HistoryManager* initializeHashHistory ();

/**
 * @brief Deletes all the contents of the history hash table and frees the pointer to the history manager.
 *
 * @param h_mngr Pointer to the history manager.
 */
void freeHistory (HistoryManager* h_mngr);

/**
 * @brief Traverses the history by music and applies a callback function to each element.
 *
 * @param mngr Pointer to the history manager.
 * @param callback A callback function to be executed for each element.
 * @param data Additional data to pass to the callback function.
 */
void traverseHistorybyMusic(HistoryManager* mngr, void (callback)(gpointer key, gpointer value, gpointer query_data), gpointer data);

/**
 * @brief Traverses the history by user and applies a callback function to each element.
 *
 * @param mngr Pointer to the history manager.
 * @param callback A callback function to be executed for each element.
 * @param data Additional data to pass to the callback function.
 */
void traverseHistorybyUser(HistoryManager* mngr, void (callback)(gpointer key, gpointer value, gpointer query_data), gpointer data);


/**
 * @brief Parses history dataset and checks for validity, writing to error logs if it fails.
 *
 * @param path A string with the path to the history dataset.
 * @param mngr Pointer to the history manager.
 *
 * @return Returns 1 for error, 0 for success.
 */
int getDataHistory (char *path, HistoryManager* mngr);

/**
 * @brief Returns the size of the history hashtable
 * 
 * @param mngr Pointer to the history manager.
 * 
 * @return How many elements the history hashtable has.
 */
int lengthHistory (HistoryManager* mngr);

/**
 * @brief Transforms the History hashtable into an History array.
 * 
 * @param mngr Pointer to the history manager.
 * @param hash
 */
int transformHistory (HistoryManager* manager, History*** hashArray);

// trees

/**
 * @brief Allocates memory and initializes the history hash tree.
 *
 * @return A pointer to the initialized history manager, where the history tree is stored.
 */
void initializeHistoryTree(HistoryManager* mngr);

/**
 * @brief A function that receives Date types and compares them, meant to be used in a glib function.
 * 
 * @param a Date 1 to be compared.
 * @param b Date 2 to be compared.
 * @param data Parameter not used.
 * 
 * @return Returns 0 if the dates are the same, 1 if a is older than b, and -1 if b is older than a.
 */
gint compareDateGlib(const void* a, const void* b, gpointer user_data);

/**
 * @brief Creates and sorts a tree with historys.
 *
 * Iterates through the history records stored in the history manager, processes each record using a provided 
 * callback function. It then calls #filterToTree and the hash table is filtered and transformed into a tree 
 * structure stored in the history manager.
 *
 * @param manager Pointer to the HistoryManager, which stores the history data and the tree.
 * @param processHistory Callback function used to process each history record. 
 * @param m_mngr Pointer to the MusicManager to feed the callback function.
 */
void createAndSortTree (HistoryManager* manager, void (processHistory) (History*, MusicManager*, GHashTable*), MusicManager* m_mngr);


/**
 * @brief Filters a hash table to a tree stored in HistoryManager. This function is only used in Q4.
 * The given hash table stores another, smaller hash trees, each containing a tuple of an artist ID and their listening time. 
 * Each of these small tables will get converted to an array and sorted by the time in the tuple. This will then get filtered,
 * only keeping the top 10 artists and finally stored in the tree, using the same key of the hash table as key for the tree node.
 * 
 * @param mngr Pointer to the history manager, where the tree is stored.
 * @param hash Pointer to the big hash table, that will get iterated.
 */
void filterToTree (HistoryManager* mngr, GHashTable* tree);


/**
 * @brief Checks if the history tree is initialized.
 *
 * @param mngr Pointer to the history manager.
 *
 * @return Returns true if the tree is initialized, false otherwise.
 */
bool historyTreeIsInitialized (HistoryManager* mngr);

/**
 * @brief Traverses the history tree and applies a callback function to each element.
 *
 * @param mngr Pointer to the history manager.
 * @param callback A callback function to be executed for each element.
 * @param feeder Additional data to pass to the callback function.
 */
void traverseTree(HistoryManager* mngr, gboolean callback(gpointer key, gpointer value, gpointer user_data), gpointer feeder);

/**
 * @brief Callback function used during history parsing.
 * Checks if the tokens received during parsing create a valid history entry. 
 * Valid entries are added to the hash table; invalid ones go to error logs.
 *
 * @param tokens An array of strings with the tokens to be used.
 * @param manager The history manager.
 * @param output The error file structure.
 */
void callbackHistory(char **tokens, void *manager, Output *output);


History* lookupHistoryHashByUser (HistoryManager *h_mngr, int id);

#endif