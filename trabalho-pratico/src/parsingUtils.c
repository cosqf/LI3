#include <parsingUtils.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <utils.h>


    
// Validating the user's birthdate, ensuring it's in the correct format and not more recent than 09/09/2024
Date parseDate(char* dateStr) {
    Date date;

    if (sscanf(dateStr, "%d/%d/%d", &date.year, &date.month, &date.day) != 3) date.error = 1;
    else if (date.year > 2024) date.error = 1;
    else if (date.year == 2024){
        if (date.month > 9) date.error = 1;
        if (date.month == 9 && (date.day < 1 || date.day > 9)) date.error = 1;
    }
    else if (date.month < 1 || date.month > 12 || date.day < 1 || date.day > 31) date.error = 1;
    else date.error = 0;

    return date;
}

int* parseIDs(char *line, void* IDnum, DataType type) {
    if (line == NULL) return NULL;

    char * token = NULL;
    int *ids = NULL;
    int count=0;

    int len = strlen (line);
    if (line [len - 1] == '\n') line [len - 1] = '\0';
    line = trimString (line);

    if (strlen (line) == 0) {
        updateCount (IDnum, type, count);
        return NULL;
    }

    for (count = 0; (token = strsep (&line, ",")) != NULL; count ++) {
        token = trimString (token);
        if (token == NULL) break;
        if (token[0] == 'S' || token[0] == 'A') {
            ids = realloc (ids, sizeof(int) * (count + 1));
            if (ids == NULL) {
                perror ("Realloc error");
                exit (EXIT_FAILURE);
            }
            ids[count] = atoi (token + 1);
        }
    }
    updateCount (IDnum, type, count);
    return ids;
}


int IdCounter (char* id_counter){
    if (!id_counter) return 0; 

    int count = 0;
    char *token = NULL;

    // Fetching the ID
    token = trimString(strsep(&id_counter, ","));
    while(token){
        if (strlen(token) > 0) {
            count++;
        }
        token = trimString(strsep(&id_counter, ","));
    }
    
    return count;
}