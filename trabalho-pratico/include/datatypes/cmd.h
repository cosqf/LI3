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

void setCMDQuery(CMD* cmd, int query);

void setCMDEntity(CMD* cmd, char entity);

void setCMDId(CMD* cmd, int id);

void setCMDTopN(CMD* cmd, int topN);

void setCMDCountry(CMD* cmd, const char* paises);

void setCMDAgeMin(CMD* cmd, int ageMin);

void setCMDAgeMax(CMD* cmd, int ageMax);

void setCMDDateMin(CMD* cmd, Date dateMin);

void setCMDDateMax(CMD* cmd, Date dateMax);

void setCMDNoUsers(CMD* cmd, int noUsers);

void setCMDYear(CMD* cmd, short int year);

void setCMDNArtists(CMD* cmd, short int nArtists);
#endif