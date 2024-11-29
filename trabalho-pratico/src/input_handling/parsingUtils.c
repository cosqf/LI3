#include <parsingUtils.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <utils.h>

Timestamp parseTimestamp (char* string) {
    char* date = strsep (&string, " ");
    Timestamp timestamp;
    timestamp.date = parseDate (date);
    timestamp.hour = parseDuration (trimString (string));
    return timestamp;
}

Date parseDate(char* dateStr) {
    Date date;

    if (sscanf(dateStr, "%d/%d/%d", &date.year, &date.month, &date.day) != 3) date.error = 1;
    else date.error = 0;

    return date;
}


Duration parseDuration(char* dur) {
    Duration duration = {0, 0, 0, 0};

    if (strlen(dur) > 8) {
        duration.error = 1;
        return duration;
    }

    if (sscanf(dur, "%d:%d:%d", &duration.hours, &duration.minutes, &duration.seconds) != 3) duration.error = 1;

    return duration;
}


int* parseIDs(char *line) {
    if (line == NULL) return NULL;

    char *copy = strdup(line);

    int* ids = NULL;
    int count = 0;

    char *token;
    char *copyPtr = copy;
    while ((token = strsep(&copyPtr, ",")) != NULL) {

        while (*token == ' ' || *token == '\'' || *token == 'U' || *token == 'S' || *token == 'A' || *token == '[' || *token == ']') token++;
        if (*token == '\0') continue;
        char *end = token + strlen(token) - 1;
        while (end >= token && (*end == ' ' || *end == '\'' || *end == 'U' || *end == 'S' || *end == 'A' || *end == ']' || *end == '[')) {
            end--;
        }
        *(end + 1) = '\0';

        int id;
        if (!convertToInt (token, &id)) {
            fprintf(stderr, "Conversion error for token: %s\n", token);
            free(ids);
            free(copy);
            exit(EXIT_FAILURE);
        }

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
    free(copy);
    return ids;
}


int IdCounter(char* id_counter) {
    if (!id_counter) return 0; 

    char* copy = strdup(id_counter);
    char* copyPtr = copy;

    int count = 0;
    char* token = NULL;

    token = trimString(strsep(&copy, ","));
    while (token) {
        if (strlen(token) > 0) {
            count++;
        }
        token = trimString(strsep(&copy, ","));
    }

    free(copyPtr);

    return count;
}
