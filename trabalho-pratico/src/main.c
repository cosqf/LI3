#include <parsingUtils.h>
#include <getdata.h>
#include <query1.h>
#include <stdlib.h>
#include <utils.h>
#include <freeFunctions.h>
#include <parsingCmd.h>


int main (int argc, char** argv) { // argv[1]: path to data, argv[2]: cmd
    if (argc != 3) {
        perror ("Wrong number of arguments");
        return 1;
    }
    FILE *fp = openFile (argv[2]);

    getData (argv[1]);

    char str[DEFAULT];
    while (fgets (str, sizeof str, fp) != NULL){
        CMD *cmd = malloc (sizeof(CMD));
        if (mallocErrorCheck (cmd)) exit (EXIT_FAILURE);

        cmd = getCommand (str, cmd);
        //if (cmd->query == 1) query1 (argv[1]);
        freeCmd (cmd);
    }

    fclose (fp);
}