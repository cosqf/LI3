#include <cmd.h>
#include <userManager.h>
#include <musicManager.h>

#ifndef _QUERY3_H_
#define _QUERY3_H_

/**
 * @brief A tuple holding a string of the genre and its respective likes.
 */
typedef struct {
    char* genre;
    int likes;
} TupleMusics;

/**
 * @brief A struct to hold the data to feed.
 */
typedef struct {
    int ageMin, ageMax;
    TupleMusics* arrayResults;
    MusicManager* m_mngr;
} q3Data;

/**
 * @brief Determines the most popular music genre in a given age group.
 * This function iterates over every @c User , first checking if they fit the desired age range, and if so,
 * processing their liked musics list to determine the most recurrent music genre in said age group.
 * 
 * @param cmd A pointer to the command struct.
 * @param u_mngr A pointer to a user manager.
 * @param m_mngr A pointer to a music manager.
 * @param cmdCounter A counter with the number of the command. 
 */
void query3 (CMD *cmd, UserManager *u_mngr, MusicManager *m_mngr, int cmdCounter);

/**
 * @brief This function processes a user's liked musics list, keeping an array with counters for each genre.
 * 
 * @param key Unused parameter.
 * @param value A pointer to a User.
 * @param data A pointer to a @c q3Data.
 */
void q3ProcessUsers(gpointer key, gpointer value, gpointer data);

/**
 * @brief Increments the number of likes of the genre in the given array.
 * 
 * @param array An array of @c TupleMusics.
 * @param genre An enum of the genre.
 */
void addToResults(TupleMusics *array, Genre genre);

/**
 * @brief Assigns a @c TupleMusics array with a specific genre and sets all the likes at 0.
 * 
 * @param array The array to be assigned.
 */
void defineGenre (TupleMusics *array);

/**
 * @brief Compares two @c TupleMusics by the number of likes and alphabetically.
 * 
 * @param a First tuple to compare.
 * @param b Second tuple to compare.
 * 
 * @return Returns 1 if b has more likes, -1 if a has more likes and 0 if theyre equal (Descending order).
 */
int compareLikes(const void* a, const void* b);

#endif