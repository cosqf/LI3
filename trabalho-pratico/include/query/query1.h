#include <parsingUtils.h>
#include <cmd.h>
#include <userManager.h>
#include <artistManager.h>
#include <musicManager.h>
#include <users.h>

#ifndef _QUERY1_H_
#define _QUERY1_H_

/**
 * @brief Structure representing a feeder for the callback functions used in Q1.
 */
typedef struct q1feeder {
    Artist* artist;
    AlmightyManager* mngr;
    double total;
} Q1Feeder;

/**
 * @brief
 * 
 * @param cmd A pointer to the command struct.
 * @param mngr A pointer to the main manager.
 * @param cmdCounter A counter with the number of the command. 
 */
void query1(CMD*, AlmightyManager* mngr, int);

/**
 * @brief Prints the user info.
 * 
 * @param cmd A pointer to a CMD struct.
 * @param mngr A pointer to the main manager.
 * @param artist A pointer to the user we will print.
 * @param file A pointer to an Output struct, which has the file we will print to.
 */
void userinfo (CMD* cmd, User* user, Output* file);

/**
 * @brief Prints the artist info.
 * 
 * @param cmd A pointer to a CMD struct.
 * @param mngr A pointer to the main manager.
 * @param artist A pointer to the artist we will print.
 * @param file A pointer to an Output struct, which has the file we will print to.
 */
void artistinfo (CMD* cmd, AlmightyManager* mngr, Artist* artist, Output* file);

/**
 * @brief Calculates how many albums an artist has made.
 * 
 * @param mngr A pointer to the main manager.
 * @param A pointer to the artist we want to know the number of albums.
 * 
 * @return The number of albums.
 */
int individualAlbums (AlmightyManager* mngr, Artist* artist);

/**
 * @brief Calculates the total recipe an artist gains.
 * 
 * @param mngr A pointer to the history manager.
 * @param artist A pointer to the artist.
 * 
 * @return The total recipe of the artist.
 */
double totalRecipe (AlmightyManager* mngr, Artist* artist);

/**
 * @brief Callback function to calculate the total recipe an individual artist gains.
 * 
 * @param key The music ID to which the history entry is associated.
 * @param value The first history entry associated to said music.
 * @param data A pointer to a Q1Feeder.
 */
void singleArtist (gpointer key, gpointer value, gpointer data);

/**
 * @brief Callback function to calculate the total recipe a group gains.
 * 
 * @param key The music ID to which the history entry is associated.
 * @param value The first history entry associated to said music.
 * @param data A pointer to a Q1Feeder.
 */
void collectiveArtist (gpointer key, gpointer value, gpointer data);

#endif  
