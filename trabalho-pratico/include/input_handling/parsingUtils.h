#ifndef _PARSINGUTILS_H_
#define _PARSINGUTILS_H_

/**
 * @brief Default buffer size used in parsing.
 */
#define DEFAULT 2000

/**
 * @brief Enumeration of data types used in the dataset.
 */
typedef enum { 
    Users = 1,    /**< User datatype */
    Artists,      /**< Artist datatype */
    Musics,       /**< Music datatype */
    Historys,     /**< History datatype */
    Albums        /**< Album datatype */
} DataType;

/**
 * @brief Calendar date structure
 */
typedef struct {
    int year;          /**< Year (format: YYYY, valid values <= 2024). */
    int month;         /**< Month (valid range: 01–12). */
    int day;           /**< Day (valid range: 01–31). */
    short int error;   /**< Error flag (0 = valid, 1 = invalid). */
} Date;

/**
 * @brief Time duration.
 */
typedef struct {
    int hours;         /**< Hours (valid range: 00–99). */
    int minutes;       /**< Minutes (valid range: 00–59). */
    int seconds;       /**< Seconds (valid range: 00–59). */
    short int error;   /**< Error flag (0 = valid, 1 = invalid). */
} Duration;

/**
 * @brief Represents a timestamp with date and time.
 * 
 * This structure combines a @c Date and a @c Duration.
 */
typedef struct timestamp {
    Date date;         /**< The date component of the timestamp. */
    Duration hour;     /**< The time component of the timestamp. */
} Timestamp;


/**
 * @brief Parses a @c Timestamp type from a string
 *  
 * This function separates the date and the time and then uses #parseDate and #parseDuration.
 * 
 * @param string The string that will be read, in the format "YYYY/MM/DD HH:MM:SS".
 * 
 * @return The timestamp type represented in the given string.
 */
Timestamp parseTimestamp (char* string);

/**
 * @brief Parses a @c Date type from a string
 * 
 * This function reads a date in the YYYY/MM/DD format, using sscanf,
 * and if the format is wrong it sets an error flag. 
 * 
 * @param string The string that will be read.
 * 
 * @return The date type represented in the given string.
 */
Date parseDate(char*);

/**
 * @brief Parses a @c Duration type from a string
 * 
 * This function reads a duration in the HH:MM:SS format, using sscanf,
 * and if the format is wrong it sets an error flag.
 * 
 * @param string The string that will be read.
 * 
 * @return The duration type represented in the given string.
 */
Duration parseDuration(char*);

/**
 * @brief Parses a list of IDs from a string to an array of numbers.
 * 
 * This function reads a string with many IDs, a 'A', 'S' or 'U' followed by 7 digits. 
 * The list starts and ends with straight brackets '[]', each ID is separated by a comma ',' and
 * is inside single quotation marks ('). If the conversion of the ID to @c int fails, the program
 * frees the memory and exits.
 * 
 * @param string The string that will be read, following the list of IDs format.
 * 
 * @return An array of @c int, with the IDs as numbers.
 */
int* parseIDs(char *);





char* trimString (char *);





/**
 * @brief Counts how many IDs are in a string, separated by commas.
 * 
 * This function parses a string containing IDs separated by commas and counts the number of valid (non-empty) entries. 
 * It trims leading and trailing whitespace from each token before evaluating it.
 * 
 * @param string A string containing IDs separated by commas, or NULL.
 * 
 * @return The number of valid IDs in the string. Returns 0 if the input string is NULL.
 */
int IdCounter (char*);

#endif  
