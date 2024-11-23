#include <utils.h>
#include <stdlib.h>
#include <stdio.h>
#include <users.h>
#include <musics.h>
#include <artists.h>
#include <parsingUtils.h>
#include <string.h>
#include <glib.h>
#include <output_handling/errorfiles.h>
#include <parsing.h>
#include <validateDatatypes.h>
#include <hashtableManager.h>
#include <artistManager.h>
#include <userManager.h>
#include <musicManager.h>
#include <errno.h>
#include <limits.h>

FILE* openFile (char * argv) { 
    FILE* fp = fopen (argv, "r");
        if (!fp) {
            perror("Error: File didn't open");
            return NULL;
        }
    return fp;
}

bool mallocErrorCheck (void* address) {
    if (address == NULL) {
        perror ("Malloc error");
        return 1;
    }
    else return 0;
}

char *trimString(char *str) {
    if (!str) return NULL;

    char *start = str;
    char *end = str + strlen(str) - 1;

    while (*start == '"' || *start == ' ' || *start == '\'' || *start == '[' || *start == ']' || *start == '\'') {
        start++;
    }

    while (end > start && (*end == '"' || *end == ' ' || *end == '\'' || *end == '\n' || *end == '[' || *end == ']' || *end == '\'')) {
        *end-- = '\0';
    }

    return start; 
}

char* trimStringWithoutBrackets (char* str) {
    if (!str) return NULL;

    char *start = str;
    char *end = str + strlen(str) - 1;

    while (*start == '"' || *start == ' ' || *start == '\'') {
        start++;
    }

    while (end > start && (*end == '"' || *end == ' ' || *end == '\'' || *end == '\n')) {
        *end-- = '\0';
    }

    return start; 
}

// needs to be freed by whoever calls it
char** lower (char** line) {
    char** lineCopy = strdup (line);
    for(int i = 0; lineCopy[i]; i++) lineCopy[i] = tolower(lineCopy[i]);
    return lineCopy;
}

// Checks if the given character is an undercase letter
int isletter(char a){
    if (a >= 'a' && a <= 'z') return 1;
    return 0;
}


// Checks if the given character is a digit
int isDigit(char a){
    if (a >= '0' && a <= '9') return 1;
    return 0;
}


// Checks is the given string is comprised of only undercase letters (if the flag is 0), or comprised of undercase letters and digits (if the flag is 1)
int isstr(char* str, int flag) {
    if (!str) return 0;
    
    int i;

    if (flag == 1) for (i = 0; isletter(str[i]) || isDigit(str[i]); i++);

    else for (i = 0; isletter(str[i]); i++);
    
    if (str[i] == '\0') return 1;
    
    return 0;
}

// Returns a duration in seconds
int durationInSeconds (Duration time) {
    return time.hours*3600 + time.minutes*60 + time.seconds;
}
// Returns the duration when given seconds
Duration secondsInDuration (int seconds) {
    Duration dur;
    dur.hours = seconds / 3600;
    dur.minutes = (seconds % 3600) / 60;
    dur.seconds = seconds % 60;

    return dur;
}


GHashTable* createHash () {
    return g_hash_table_new(g_direct_hash, g_direct_equal);
}

void deleteHash (GHashTable* hash) {
    g_hash_table_destroy (hash);
}

void insertHash (GHashTable* hash, int key, int value) {
    g_hash_table_insert(hash, GINT_TO_POINTER (key), GINT_TO_POINTER (value));
}


char* durationInString(Duration time) {
    char* str = malloc(9 * sizeof(char));
    if (mallocErrorCheck (str)) exit (EXIT_FAILURE);

    sprintf(str, "%02d:%02d:%02d", time.hours, time.minutes, time.seconds);

    return str; 
}

// Function to safely convert a string to int with error handling
bool convertToInt(const char *str, int *out) {
    char *endptr;
    errno = 0; 
    long val = strtol(str, &endptr, 10); 

    // Error handling: check for overflow and underflow
    if (errno == ERANGE) {
        if (val == LONG_MAX) {
            ferror("Overflow: value is too large.\n");
        } else if (val == LONG_MIN) {
            ferror("Underflow: value is too small.\n");
        }
        return false;
    }

    // Check if no digits were found
    if (endptr == str) {
        ferror("Invalid input: No digits were found.\n");
        return false;
    }

    // Check if there were any leftover characters
    if (*endptr != '\0') {
        ferror("Invalid input: Non-numeric characters found\n");
        return false;
    }

    // Check if the value fits within the range of int
    if (val < INT_MIN || val > INT_MAX) {
        ferror("Error: Value is out of int range.\n");
        return false;
    }

    *out = (int)val;
    return true;
}

int compareDate(Date dateA, Date dateB) { // if a > b returns -1, a < b returns 1, 0 otherwise
    if (dateA.year > dateB.year) return -1; 
    if (dateA.year < dateB.year) return 1;
    if (dateA.month > dateB.month) return -1;
    if (dateA.month < dateB.month) return 1;
    if (dateA.day > dateB.day) return -1;
    if (dateA.day < dateB.day) return 1;

    return 0;
}
