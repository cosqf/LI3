#include <parsingUtils.h>
#include <getdata.h>
#include <stdlib.h>
#include <utils.h>
#include <parsingCmd.h>
#include <query1.h>
#include <query2.h>
#include <entityManager.h>

int main (int argc, char** argv) { // argv[1]: path to data, argv[2]: cmd
    if (argc != 3) {
        perror ("Wrong number of arguments");
        return 1;
    }

    EntityManager* mngr = initializeHash ();

    getData (argv[1], mngr);

    //writeUsersToErrorFile(getUserTable (getUserManager(mngr)));
    //writeArtistsToErrorFile(getArtistTable (getArtistManager(mngr)));
    //writeMusicsToErrorFile(getMusicTable (getMusicManager(mngr)));

    FILE *fp = openFile (argv[2]);

    char str[DEFAULT];
    while (fgets (str, sizeof str, fp) != NULL){
        CMD *cmd = createCMD ();

        cmd = getCommand (str, cmd);
        switch (getCMDquery (cmd)) {
        case 1:
            query1 (cmd);
            break;
        case 2:
            query2 (cmd, mngr);
            break;
        case 3:
            //query3 (cmd);
            break;
        default:
            perror ("CMD ERROR");
            exit (EXIT_FAILURE);
        }

        freeCmd (cmd);
    }
    
    fclose (fp);
}