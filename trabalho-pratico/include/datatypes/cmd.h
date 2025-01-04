#include <parsingUtils.h>

#ifndef _CMD_H_
#define _CMD_H_

/**
 * @brief A command struct.
 */
typedef struct cmd CMD;

/**
 * @brief Creates a command struct.
 *
 * @param tokens An array of parsed tokens.
 * @param count A counter for the number of tokens.
 * 
 * @return A pointer to a command struct.
 */
CMD* createCMD(char** tokens, int count);

/**
 * @brief Deletes a command struct and frees its memory.
 *
 * @param cmd A pointer to the command struct to be freed.
 */
void freeCmd (CMD *cmd);

/**
 * @brief Creates an empty command struct
 * 
 * @return A pointer to a command struct.
 */
CMD* createEmptyCMD ();

/* Getters */
/**
 * @brief A getter function that returns the number of the query of the command.
 *
 * @param cmd A pointer to the command struct.
 * 
 * @return Number of the query of the given command.
 */
int getCMDquery (CMD* cmd);

/**
 * @brief A getter function that returns the entity type (Artist or User) of the command (Query 1).
 *
 * @param cmd A pointer to the command struct.
 * 
 * @return Entity type of the given command.
 */
char getCMDentity (CMD* cmd);

/**
 * @brief A getter function that returns the ID specified in the command (Query 1).
 *
 * @param cmd A pointer to the command struct.
 * 
 * @return ID specified in the given command.
 */
int getCMDId (CMD* cmd);

/**
 * @brief A getter function that returns the top N value specified in the command (Query 2).
 *
 * @param cmd A pointer to the command struct.
 * 
 * @return Top N value specified in the given command.
 */
int getCMDtopN (CMD* cmd);

/**
 * @brief A getter function that returns the country specified in the command (Query 2).
 *
 * @param cmd A pointer to the command struct.
 * 
 * @return Country specified in the given command.
 */
char *getCMDCountry (CMD* cmd);

/**
 * @brief A getter function that returns the minimum age specified in the command (Query 3).
 *
 * @param cmd A pointer to the command struct.
 * 
 * @return Minimum age specified in the given command.
 */
int getCMDAgeMin (CMD* cmd);

/**
 * @brief A getter function that returns the maximum age specified in the command (Query 3).
 *
 * @param cmd A pointer to the command struct.
 * 
 * @return Maximum age specified in the given command.
 */
int getCMDAgeMax (CMD* cmd);

/**
 * @brief A getter function that returns the separator character specified in the command.
 *
 * @param cmd A pointer to the command struct.
 * 
 * @return Separator character specified in the given command.
 */
char getCMDSeparator (CMD* cmd);

/**
 * @brief A getter function that returns the minimum date specified in the command (Query 4).
 *
 * @param cmd A pointer to the command struct.
 * 
 * @return Minimum date specified in the given command.
 */
Date getCMDdateMin (CMD* cmd);

/**
 * @brief A getter function that returns the maximum date specified in the command (Query 4).
 *
 * @param cmd A pointer to the command struct.
 * 
 * @return Maximum date specified in the given command.
 */
Date getCMDdateMax(CMD* cmd);

/**
 * @brief A getter function that returns the number of users specified in the command (Query 5).
 *
 * @param cmd A pointer to the command struct.
 * 
 * @return Number of users specified in the given command.
 */
int getCMDnoUsers(CMD* cmd);

/**
 * @brief A getter function that returns the year specified in the command (Query 6)
 *
 * @param cmd A pointer to the command struct.
 * 
 * @return Year specified in the given command.
 */
short int getCMDyear(CMD* cmd);

/**
 * @brief A getter function that returns the number of artists specified in the command (Query 6).
 *
 * @param cmd A pointer to the command struct.
 * 
 * @return Number of artists specified in the given command.
 */
short int getCMDnArtists(CMD* cmd);


/* Setters */

/**
 * @brief A setter function that sets the command query number.
 * 
 * @param cmd A pointer to the command struct.
 * @param query The number to set the query as.
 */
void setCMDQuery(CMD* cmd, int query);

/**
 * @brief Sets the entity type for the command.
 * 
 * @param cmd A pointer to the command struct.
 * @param entity The character representing the entity type ('U' for user, 'A' for artist).
 */
void setCMDEntity(CMD* cmd, char entity);

/**
 * @brief Sets the ID parameter for the command.
 * 
 * @param cmd A pointer to the command struct.
 * @param id The ID to associate with the command.
 */
void setCMDId(CMD* cmd, int id);

/**
 * @brief Sets the top N parameter for the command.
 * 
 * @param cmd A pointer to the command struct.
 * @param topN The number of top results to associate with the command.
 */
void setCMDTopN(CMD* cmd, int topN);

/**
 * @brief Sets the country filter for the command.
 * 
 * @param cmd A pointer to the command struct.
 * @param paises A string containing the country to filter by.
 */
void setCMDCountry(CMD* cmd, const char* paises);

/**
 * @brief Sets the minimum age filter for the command.
 * 
 * @param cmd A pointer to the command struct.
 * @param ageMin The minimum age to filter by.
 */
void setCMDAgeMin(CMD* cmd, int ageMin);

/**
 * @brief Sets the maximum age filter for the command.
 * 
 * @param cmd A pointer to the command struct.
 * @param ageMax The maximum age to filter by.
 */
void setCMDAgeMax(CMD* cmd, int ageMax);

/**
 * @brief Sets the minimum date filter for the command.
 * 
 * @param cmd A pointer to the command struct.
 * @param dateMin The earliest date allowed in the results.
 */
void setCMDDateMin(CMD* cmd, Date dateMin);

/**
 * @brief Sets the maximum date filter for the command.
 * 
 * @param cmd A pointer to the command struct.
 * @param dateMax The latest date allowed in the results.
 */
void setCMDDateMax(CMD* cmd, Date dateMax);

/**
 * @brief Sets the number of users for the command.
 * 
 * @param cmd A pointer to the command struct.
 * @param noUsers The number of users to associate with the command.
 */
void setCMDNoUsers(CMD* cmd, int noUsers);

/**
 * @brief Sets the year filter for the command.
 * 
 * @param cmd A pointer to the command struct.
 * @param year The year to filter results by.
 */
void setCMDYear(CMD* cmd, short int year);

/**
 * @brief Sets the number of artists for the command.
 * 
 * @param cmd A pointer to the command struct.
 * @param nArtists The number of artists to associate with the command.
 */
void setCMDNArtists(CMD* cmd, short int nArtists);

#endif