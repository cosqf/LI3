#include <processInput.h>
#include <getdata.h>
#include <query1.h>
#include <stdlib.h>
#include <stdio.h>

int main (int argc, char** argv) {
    if (argc != 3) {
        perror ("Wrong number of arguments");
        return 1;
    }
    FILE* fp = fopen (argv[2], "r");
        if (!fp) {
            perror("Error: File didn't open");
            return 1;
        }

    CMD *cmd = malloc (sizeof(CMD));
    if (cmd == NULL) {
        perror ("Malloc Error");
            return 1;
    }

    getData (argv[1]);

    char str[DEFAULT];
    while (fgets (str, sizeof str, fp) != NULL){
        cmd = getCommand (str, cmd);
        //if (cmd->query == 1) query1 (argv[1]);
    }

    fclose (fp);

    if (cmd) freeCmd (cmd);

}