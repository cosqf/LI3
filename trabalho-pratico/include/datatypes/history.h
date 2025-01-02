#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <parsingUtils.h>

#ifndef _HISTORY_H_
#define _HISTORY_H_

/**
 * @brief A history struct.
 */
typedef struct history History;

/**
 * @brief History struct where every component is in a string format.
 */
typedef struct historyString HistoryString;

/**
 * @brief Creates a history struct.
 *
 * @param tokens An array of parsed tokens.
 * 
 * @return A pointer to a history struct.
 */
History* createHistory (char** tokens);

/**
 * @brief Deletes a history struct and frees its memory.
 *
 * @param history A pointer to the history struct to be deleted.
 */
void deleteHistoryByUser (History* history);

/**
 * @brief Creates a history struct in string format.
 *
 * @param tokens An array of parsed tokens.
 * 
 * @return A pointer to a history string struct.
 */
HistoryString* createHistoryString (char** tokens);

/**
 * @brief Deletes a history string struct and frees its memory.
 *
 * @param history A pointer to the history string struct to be deleted.
 */
void deleteHistoryString (HistoryString* history);


/* Getters */
/**
 * @brief A getter function that returns the ID of a history entry.
 *
 * @param history A pointer to the history struct.
 * 
 * @return ID of the given history entry.
 */
int getHistoryId (History* history);

/**
 * @brief A getter function that returns the user ID associated with a history entry.
 *
 * @param history A pointer to the history struct.
 * 
 * @return User ID of the given history entry.
 */
int getHistoryUserId (History* history);

/**
 * @brief A getter function that returns the music ID associated with a history entry.
 *
 * @param history A pointer to the history struct.
 * 
 * @return Music ID of the given history entry.
 */
int getHistoryMusicId (History* history);

/**
 * @brief A getter function that returns the timestamp of a history entry.
 *
 * @param history A pointer to the history struct.
 * 
 * @return Timestamp of the given history entry.
 */
Timestamp getHistoryTimestamp (History* history);

/**
 * @brief A getter function that returns the duration of a history entry.
 *
 * @param history A pointer to the history struct.
 * 
 * @return Duration of the given history entry.
 */
Duration getHistoryDuration (History* history);

/**
 * @brief A getter function that returns the next history entry by user.
 *
 * @param history A pointer to the current history struct.
 * 
 * @return Pointer to the next history entry by user.
 */
History* getNextHistoryByUser (History* history);

/**
 * @brief A getter function that returns the next history entry by music.
 *
 * @param history A pointer to the current history struct.
 * 
 * @return Pointer to the next history entry by music.
 */
History* getNextHistoryByMusic (History* history);

/**
 * @brief A getter function that returns the length of the history list by user.
 *
 * @param history A pointer to the history struct.
 * 
 * @return Length of the history list by user.
 */
int getHistoryListLengthByUser(History* history);

/**
 * @brief A getter function that returns the length of the history list by music.
 *
 * @param history A pointer to the history struct.
 * 
 * @return Length of the history list by music.
 */
int getHistoryListLengthByMusic(History* history);





History* copyHistoryByUser( History* historyOg);



/* Getters string */
/**
 * @brief A getter function that returns the ID of a history entry in string format.
 *
 * @param history A pointer to the history string struct.
 * 
 * @return ID of the given history entry in string format.
 */
char* getHistoryIdString (HistoryString* history);

/**
 * @brief A getter function that returns the user ID associated with a history entry in string format.
 *
 * @param history A pointer to the history string struct.
 * 
 * @return User ID of the given history entry in string format.
 */
char* getHistoryUserIdString (HistoryString* history);

/**
 * @brief A getter function that returns the music ID associated with a history entry in string format.
 *
 * @param history A pointer to the history string struct.
 * 
 * @return Music ID of the given history entry in string format.
 */
char* getHistoryMusicIdString (HistoryString* history);

/**
 * @brief A getter function that returns the timestamp of a history entry in string format.
 *
 * @param history A pointer to the history string struct.
 * 
 * @return Timestamp of the given history entry in string format.
 */
char* getHistoryTimestampString (HistoryString* history);

/**
 * @brief A getter function that returns the duration of a history entry in string format.
 *
 * @param history A pointer to the history string struct.
 * 
 * @return Duration of the given history entry in string format.
 */
char* getHistoryDurationString (HistoryString* history);

/**
 * @brief A getter function that returns the platform of a history entry in string format.
 *
 * @param history A pointer to the history string struct.
 * 
 * @return Platform of the given history entry in string format.
 */
char* getHistoryPlatformString (HistoryString* history);


/* Setters*/
/**
 * @brief A setter function that sets the next history entry by user.
 *
 * @param newNext A pointer to the new history entry.
 * @param history A pointer to the current history entry.
 * 
 * @return Pointer to the updated history entry.
 */
History* setNextHistoryByUser (History* newNext, History* history);

/**
 * @brief A setter function that sets the next history entry by music.
 *
 * @param newNext A pointer to the new history entry.
 * @param history A pointer to the current history entry.
 * 
 * @return Pointer to the updated history entry.
 */
History* setNextHistoryByMusic (History* newNext, History* history);

#endif