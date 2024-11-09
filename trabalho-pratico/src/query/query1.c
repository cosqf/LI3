#include <stdlib.h>
#include <query1.h>
#include <parsing.h>
#include <userManager.h>
#include <users.h>
#include <stdio.h>
#include <output_handling/outputWriter.h>


void query1(CMD* cmd, UserManager *u_mngr, int counter) {
    char filename[50];  // buffer for the formatted file name

    // Format the filename with the counter value
    snprintf(filename, sizeof(filename), "resultados/command%d_output.txt", counter);

    Output* output = openOutputFile (filename);

    int userID = getCMDId(cmd);
    User* user = lookupUserHash(u_mngr, userID);

    char* lines[5] = {NULL};
    
    if (user == NULL) setOutput(output, NULL, 0);
    else {
        lines[0] = getUserEmail(user);
        lines[1] = getUserFirstName(user);
        lines[2] = getUserLastName(user);

        // Formatting the age as a string
        static char ageString[4];
        snprintf(ageString, sizeof(ageString), "%d", getUserAge(user));
        lines[3] = ageString;

        lines[4] = getUserCountry(user);

        setOutput(output, lines, 5);
    }

    writeQuerys(output);

    if (user != NULL) {
        free(lines[0]);
        free(lines[1]);
        free(lines[2]);
        free(lines[4]);
    }

    closeOutputFile(output);
}