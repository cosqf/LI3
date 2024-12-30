#include <parsingUtils.h>
#include <cmd.h>
#include <userManager.h>
#include <artistManager.h>
#include <musicManager.h>
#include <users.h>

#ifndef _QUERY1_H_
#define _QUERY1_H_

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




double totalRecipe (AlmightyManager* mngr, Artist* artist);





/**
 * @brief Calculates the total recipe an individual artist gains.
 * 
 * @param hashtable A pointer to a hashtable of Historys. (?)
 * @param artist A pointer to the individual artist.
 * @param mngr A pointer to the main manager.
 * 
 * @return The total recipe of the individual artist.
 */
double singleArtist (GHashTable* hashtable, Artist* artist, AlmightyManager* mngr);

/**
 * @brief Calculates the total recipe a group gains.
 * 
 * @param hashtable A pointer to a hashtable of Historys. (?)
 * @param artist A pointer to the collective artist.
 * @param mngr A pointer to the main manager.
 * 
 * @return The total recipe of the group.
 */
double collectiveArtist (GHashTable* hashtable, Artist* artist, AlmightyManager* mngr);

#endif  
