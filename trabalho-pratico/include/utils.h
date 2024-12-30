#include <stdio.h>
#include <parsingUtils.h>
#include <stdbool.h>
#include <glib.h>
#include <musics.h>

#ifndef _UTILS_H_
#define _UTILS_H_

/**
 * @brief Opens a file in read mode.
 *
 * @param argv The path to the file to be opened.
 * 
 * @return A pointer to the opened @c FILE, or NULL if the file could not be opened.
 */
FILE* openFile (char * argv);

/**
 * @brief Checks for malloc errors.
 * Verifies if the provided pointer is NULL, which would indicate a memory allocation failure.
 * If the pointer is NULL, an error message is printed and returns true; otherwise, it returns false.
 *
 * @param address The pointer to check.
 * @return 1 if the pointer is NULL (indicating a malloc error), 0 otherwise.
 */
bool mallocErrorCheck (void* add);

/**
 * @brief Trims unwanted characters such as spaces, quotes and brackets from the beginning and end of a string.

 * @param str The string to be trimmed.

 * @return A pointer to the trimmed string.
 */
char *trimString(char *str);

/**
 * @brief Trims unwanted characters such as spaces and quotes from the beginning and end of a string.

 * @param str The string to be trimmed.

 * @return A pointer to the trimmed string.
 */
char* trimStringWithoutBrackets (char* str);

/**
 * @brief Converts a string to lowercase.
 * Creates a copy of the given string and converts all characters to lowercase.
 * The caller is responsible for freeing the returned string.
 *
 * @param line The string to be converted to lowercase.
 * 
 * @return A pointer to a newly allocated string that is the lowercase version of the input string.
 */
char* lower (char* line);

/**
 * @brief Checks if a character is a lowercase letter.

 * @param a The character to check.

 * @return 1 if the character is a lowercase letter, 0 otherwise.
 */
int isletter(char);

/**
 * @brief Checks if a character is a digit.

 * @param a The character to check.

 * @return 1 if the character is a digit, 0 otherwise.
 */
int isDigit(char);

/**
 * @brief Checks if a string is comprised of valid characters.
 * Determines if the given string is made up of either only lowercase letters (when flag is 0)
 * or lowercase letters and digits (when flag is 1).
 *
 * @param str The string to check.
 * @param flag A flag indicating which characters are allowed:

 * @return 1 if the string consists of valid characters according to the flag, 0 otherwise.
 */
int isstr(char*, int);

/**
 * @brief Creates a new hash table.
 * Allocates and initializes a new hash table with integer keys and values.
 * The hash table uses direct pointer comparison for both hashing and equality.
 *
 * @return A pointer to the newly created hash table.
 */
GHashTable* createHash ();

/**
 * @brief Deletes a hash table.

 * @param hash The hash table to delete.
 */
void deleteHash (GHashTable* hash);

/**
 * @brief Inserts a value into the hash table using a given key.
 * The key and value are converted to pointers using 'GINT_TO_POINTER'.
 *
 * @param hash The hash table.
 * @param key The key to insert.
 * @param value The value associated with the key.
 */
void insertHash (GHashTable* hash, int key, int value);

/**
 * @brief Converts a @c Duration to a string in the format "hh:mm:ss".
 * The string is dynamically allocated and must be freed by the caller.
 *
 * @param time The @c Duration to be converted.
 * 
 * @return A pointer to the formatted string.
 */
char* durationInString(Duration time);



void writeMusicsToErrorFile(GHashTable* );
void writeUsersToErrorFile(GHashTable* );
void writeArtistsToErrorFile(GHashTable* );



/**
 * @brief Safely converts a string to an integer with error handling.
 * Converts a string to an integer, performing checks for overflow, underflow,
 * and other errors. If any errors occur, an appropriate error message is printed.
 *
 * @param str The string to be converted to an integer.
 * @param out The pointer where the converted integer will be stored.
 * @return True if the conversion is successful, False otherwise.
 */
bool convertToInt(const char *str, int *out);

/**
 * @brief Compares two @c Date objects.
 * Compares two @c Date objects (year, month, day) and returns:
 * - 1 if dateA is greater than dateB
 * - -1 if dateA is smaller than dateB
 * - 0 if both dates are equal
 *
 * @param dateA The first date to compare.
 * @param dateB The second date to compare.
 * 
 * @return 1, -1, or 0 depending on the comparison result.
 */
int compareDate(Date dateA, Date dateB);



int durationInSeconds (Duration time);

Duration secondsInDuration (int seconds);



/**
 * @brief Calculates the difference in days between two dates.
 * Returns the difference in days between two dates (dateA - dateB), assuming that dateA is more recent.
 *
 * @param dateA The more recent Date.
 * @param dateB The older Date.
 * @return The difference in days between the two dates.
 */
int daysDiff(Date dateA, Date dateB);

/**
 * @brief Gets the weekday of a given date (0 = Sunday, 1 = Monday, ...).
 * Computes the weekday of a given date using a simplified version of Zeller's Congruence algorithm.
 * https://en.wikipedia.org/wiki/Zeller%27s_congruence#Common_simplification
 * 
 * @param date The Date object to compute the weekday for.
 * 
 * @return A number representing the weekday.
 */
short int getWeekday (Date date); // gotten from wikipedia, sunday == 0

/**
 * @brief Gets the number of days in a given month of a given year.
 *
 * @param month The month.
 * @param year The year.
 * @return The number of days in the specified month and year.
 */
int getDaysInMonth(int month, int year);

/**
 * @brief Calculates the total number of days since year 0 for a given date.
 * Calculates the total number of days that have passed since year 0 (epoch) for the given Date.
 *
 * @param date The Date object to calculate the number of days for.
 * @return The total number of days since year 0 for the given date.
 */
int calculateDays(Date date);

#endif