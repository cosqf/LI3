#include <stdbool.h>
#include <cmd.h>
#include <musics.h>
#include <almightyManager.h>
#include "output_handling/outputWriter.h"

#ifndef _QUERY2_H_
#define _QUERY2_H_

/**
 * @brief Calculates the top N artists with the biggest discography, with an optional country filter.
 * This function starts by iterating the music hash table; For each music it will update a temporary hash table
 * using the respective artist as key and the duration of the music as the value, if the artist belongs in the country
 * we are checking (if any is provided). It also keeps a separate array of size N, where the artists and their discographies
 * are stored in a sorted way. After, all that remains is printing the N elements of the array.
 * 
 * @param cmd A pointer to the command struct.
 * @param mngr A pointer to the main manager.
 * @param cmdCounter A counter with the number of the command. 
 */
void query2(CMD *cmd, AlmightyManager* mngr, int cmdCounter);

<<<<<<< HEAD
/**
 * @brief For each artist ID given, checks if they belong to a certain country (if any is given) and updates a hash table with a duration given.
 * 
 * @param id Array of IDs.
 * @param count The number of IDs.
 * @param newtable A pointer to a hash table where we store the data on each artist's songs duration.
 * @param country A string representing a country, used to filter the artists. If no filter is active, it will be NULL.
 * @param a_mngr A pointer to the artist manager, used to look up the artist's country.
 */
void getArtistsDiscography (int id, GHashTable* newtable, int duration, char* country, ArtistManager *a_mngr, Tuple* top10Sorted, int* minDuration);
=======
void getArtistsDiscography (int id, GHashTable* newtable, int duration, char* country, ArtistManager *a_mngr, Tuple* top10Sorted, int topN, int* minDuration);

void updateSortedArray(GHashTable* table, int id, Tuple* top10Sorted, int topN, int* minDuration);
>>>>>>> afd13d6a98a35d3449a46ec3fee26ebadc8aa408



int durationInSeconds (Duration time);

Duration secondsInDuration (int seconds);



/**
 * @brief This function feeds #getArtistsDiscography.
 * 
 * @param key Unused parameter.
 * @param value A pointer to a @c Music struct.
 * @param data A pointer to a @c FeederData
 */
void feeder(gpointer key, gpointer value, gpointer user_data);

/**
 * @brief Prints the results of the query 2.
 * 
 * @param cmd A pointer to a @c CMD struct.
 * @param artist A pointer to the artist that will be printed.
 * @param dur The duration of the artist's discography.
 * @param output A pointer to an @c Output struct.
 */
void printResult (CMD* cmd, Artist* artist, Duration dur, Output* output);

#endif  