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

    char *copy = strdup(line);

    int* ids = NULL;
    int count = 0;

    char *token;
    char *copyPtr = copy;
    while ((token = strsep(&copyPtr, ",")) != NULL) {

        while (*token == ' ' || *token == '\'' || *token == 'U' || *token == 'S' || *token == 'A' || *token == '[' || *token == ']') token++;

        int id = atoi(token);

        int* temp = realloc(ids, sizeof(int) * (count + 1));
        if (temp == NULL) {
            perror("Realloc error");
            free(ids);
            free(copy);
            exit(EXIT_FAILURE);
        }
        ids = temp;
        ids[count] = id;
        count++;
    }
    
    updateCount (IDnum, type, count);

    free(copy);
    return ids;
}



int IdCounter (char* id_counter){
    if (!id_counter) return 0; 

    char* copy = strdup(id_counter);

    int count = 0;
    char *token = NULL;

    // Fetching the ID
    token = trimString(strsep(&copy, ","));
    while(token){
        if (strlen(token) > 0) {
            count++;
        }
        token = trimString(strsep(&copy, ","));
    }
    
    free(copy);

    return count;
}