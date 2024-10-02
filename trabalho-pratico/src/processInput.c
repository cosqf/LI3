#include <processInput.h>
#include <query1.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

CMD* getCommand (char* line, CMD* cmd) {
    char *token = strsep(&line, " ");
    cmd->query = atoi(token);

    if (cmd->query == 1) {
        cmd->id = atoi (line+1);

        cmd->topN = -1;
        cmd->paises = NULL;
        cmd->ageMin = -1;
        cmd->ageMax = -1;
    }
    else if (cmd->query == 2) {
        token = strsep (&line, " ");
        cmd->topN = atoi(token);
        if (line && line[0] != '\0') {
            token = strsep(&line+1, "\"");
            cmd->paises = malloc(strlen(token) + 1);
            if (cmd->paises != NULL) strcpy(cmd->paises, token); 
            else {
                perror ("Malloc Error");
                return NULL;
            }
        }
        else cmd->paises = NULL;
        cmd->id = -1;
        cmd->ageMin = -1;
        cmd->ageMax = -1;
        }
    else if (cmd->query == 3) { // add verify to make sure ageMin < ageMax and that ageMin >= 0
        token = strsep (&line, " ");
        cmd->ageMin = atoi(token);
        cmd->ageMax = atoi(line);
        
        cmd->id = -1;
        cmd->topN = -1;
        cmd->paises = NULL;
    }
    else {
        perror ("Error getting the command from input");
        return NULL;
    }
    return cmd;
}

void getData (char *path, DataType dt) {
    if (dt == Users) strcat (path, "users.csv");
    else if (dt == Artists) strcat (path, "artists.csv");
    else if (dt == Music) strcat (path, "musics.csv");
    
    FILE* fp = fopen (path, "r");
    if (!fp) {
        perror("Error: File didn't open");
        exit(EXIT_FAILURE);
    }
    short int i = 0;
    char str[DEFAULT];
    User *user = malloc (sizeof (User));
    while (fgets (str, sizeof str, fp) != NULL){
        if (i==0) {
            i++;
            continue; // skip first line
        }

        if (dt == Users) {
            user = parseDataU (str, user);
            // filtra (user)
            // poeNaHash (user);
            printf ("%s, %s, %s, %s, %d/%d/%d, %s, %d\n", user->username, user->email, user->first_name, user->last_name, user->birth_date.year, user->birth_date.month, user->birth_date.day, user->country, user->subscription_type);
            
        }
        else if (dt == Artists) parseDataA (str);
        else parseDataM (str);
    }
    fclose(fp);
}

User* parseDataU (char *str, User *user) {
    if (!str || !user) return NULL; 

    char *token = NULL;
    printf ("%s\n\n", str);

    token = strsep(&str, "\"");
    
    token = strsep(&str +1, ";");
    user->username = token;
    token = strsep(&str, ";");
    user->email = token;
    token = strsep(&str, ";");
    user->first_name = token;
    token = strsep(&str, ";");
    user->last_name = token;
    user->birth_date = parseDate (str);
    token = strsep(&str, ";");
    user->country = token;
    token = strsep(&str, ";");
    user->subscription_type = atoi(token);
    user->liked_musics_id = parseIDs (str);
    
   return user;
}

Date parseDate(char* dateStr) {
    Date date;
    char *token = strsep(&dateStr, "/");
    date.year = atoi(token);
    token = strsep(&dateStr, "/");
    date.month = atoi(token);
    token = strsep(&dateStr, ";");
    date.day = atoi(token);
    return date;
}

int* parseIDs(char *line) {
    // Remove the square brackets '[' and ']'
    char *cleanLine = strsep(&line, "[");
    cleanLine = strsep(&line, "]");

    // Initialize dynamic array and counter
    int *ids = NULL;
    int count = 0;
    
    // Split the string by commas using strsep
    char *token;

    while ((token = strsep(&cleanLine, ",")) != NULL) {
        // Trim any leading/trailing spaces and single quotes
        token = strsep(&token, "'");

        // Check if the token starts with 'S'
        if (token != NULL && token[0] == 'S') {
            // Reallocate memory for the array to hold one more ID
            ids = realloc(ids, sizeof(int) * (count + 1));
            if (ids == NULL) {
                perror("Failed to allocate memory");
                exit(EXIT_FAILURE);
            }

            // Skip the 'S' and convert the rest to an integer
            ids[count] = atoi(token + 1);  // Skip the first character 'S'
            count++;
        }
    }

    // Set the number of IDs parsed and assign the result to the output pointer
    return ids;
}

void parseDataA (char *str) {
   // filtra ()
}

void parseDataM (char *str) {
   // filtra ()
}