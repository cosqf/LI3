#include <processInput.h>
#include <stdlib.h>
#include <stdio.h>

int main (int argc, char** argv) {
    if (argc != 3) {
        perror ("Wrong number of arguments");
        return 1;
    }
    FILE* fp = fopen (argv[1], "r");
        if (!fp) {
            perror("Error: File didn't open");
            return 1;
        }

    CMD *cmd = malloc (sizeof(CMD));
    if (cmd == NULL) {
        perror ("Malloc Error");
            return 1;
    }

    char str[DEFAULT];
    while (fgets (str, sizeof str, fp) != NULL){
        cmd = getCommand (str, cmd);
        //if (cmd->querry == 1) querry1 (cmd, argv[2]) 
    }

    fclose (fp);

    if (cmd) { // fazer função para dar free em tudo?
        if (cmd->paises) free (cmd->paises);
        free (cmd);
    }

}