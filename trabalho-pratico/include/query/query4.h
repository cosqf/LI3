#include <almightyManager.h>
#include <cmd.h>

#ifndef _QUERY4_H_
#define _QUERY4_H_

/**
 * @brief Identifies the artist that appeared most in the weekly top 10, with an optional date filter.
* This function first checks whether the tree in the HistoryManager has been initialized. If not, it initializes the tree 
 * by creating a hash table containing smaller hash tables. Each of these smaller tables stores artists and their total 
 * listening times for a given week. The larger hash table is then filtered and converted into a tree structure. 
 * Each weekly table is trimmed to retain only the top 10 artists, sorted by listening time, and stored as arrays within the tree. 
 * The first day of the week is used as the key for each entry in the tree.
 * After building the tree, the function traverses it, optionally applying a date filter. 
 * It counts how many times each artist appears in the weekly top 10 within the filtered dates. 
 * Finally, the artist with the highest occurrence is identified, and the result is printed.

 * @param cmd A pointer to the command struct.
 * @param historyManager A pointer to the history manager.
 * @param musicManager A pointer to the music manager.
 * @param artistManager A pointer to the artist manager.
 * @param cmdCounter A counter with the number of the command.  
 */
void query4 (CMD* cmd, HistoryManager* historyManager, MusicManager* musicManager, ArtistManager* artistManager, int cmdCounter);

/**
 * @brief Structure representing a list of artist IDs.
 */
typedef struct {
    int* artistsIds;
    int count;
} ArtistList;

/**
 * @brief Frees the artist Ids in the struct and then the @c ArtistList itself.
 * 
 * @param list Pointer to the @c ArtistList to free.
 */
void freeArtistList (ArtistList* list) ;
#endif