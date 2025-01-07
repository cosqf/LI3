#include <historyManager.h>
#include <artistManager.h>
#include <musicManager.h>

#include <cmd.h>

#ifndef _QUERY4_H_
#define _QUERY4_H_

/**
 * @brief Structure representing a list of artist IDs.
 */
typedef struct {
    int* artistsIds;
    int count;
} ArtistList;

/**
 * @brief Structure representing a feeder for filtering history data.
 */
typedef struct {
    Date minDay;
    Date maxDay;
    GHashTable* table;
    bool isFilterOn;
} feederHistory;

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
 * @brief Organizes listening times by week from a history record.
 * Adjusts the date to the start of the week and calculates listening durations for each artist associated with the music.  
 * Updates a hash table grouped by weeks, mapping artist IDs to their listening times.
 *
 * @param history Pointer to the history struct.
 * @param musicManager Pointer to the @c MusicManager for artist lookup.
 * @param hashWithWeeks Pointer to the weekly hash table to store the artist and listening times.
 */
void sortHistoryByWeek(History* history, MusicManager* musicManager, GHashTable* hashWithWeeks);

/**
 * @brief Updates weekly data in the hash table.

 * @param bigTable Pointer to the main hash table organized by weeks.
 * @param date Start of the week (sunday).
 * @param tuple Artist ID and listening duration pair.
 */
void updateHashWithWeeks(GHashTable* bigTable, Date date, Tuple tuple);

/**
 * @brief Counts how often artists appear in the weekly top 10, optionally applying a date filter.

 * @param key Pointer to the week's start date.
 * @param value Pointer to the @c ArtistList for that week.
 * @param dataFeed Pointer to @c feederHistory with filter settings and results.
 * @return TRUE to stop early if the date exceeds the range; FALSE otherwise.
 */
gboolean callbackHistoryQuery4(gpointer key, gpointer value, gpointer dataFeed);

/**
 * @brief This function adjustes the date to the last sunday.
 * 
 * @param date A pointer to the date to change.
 */
void adjustDateLimits(Date *date);

/**
 * @brief Frees the artist Ids in the struct and then the @c ArtistList itself.
 * 
 * @param list Pointer to the @c ArtistList to free.
 */
void freeArtistList (ArtistList* list);


// functions for glib 

/**
 * @brief Creates a @c guint to set the hash key as from a @c Date.
 * 
 * @param key A pointer to a @c Date.
 * 
 * @return A @c guint to be used as key in a hash table.
 */
guint dateHashFunc(gconstpointer key);

/** 
 * @brief A function that sees if two dates are equal, in a GEqualFunc format.
 * 
 * @param a The first date to be compared.
 * @param b The second date to be compared.
 * 
 * @return Returns true if the two dates are the same.
 */
gboolean dateEqualFunc(gconstpointer a, gconstpointer b);

#endif