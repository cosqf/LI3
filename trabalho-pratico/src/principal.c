#include <stdio.h>

#include <principal.h>
#include <parsingUtils.h>
#include <parsing.h>
#include <utils.h>
#include <cmd.h>
#include <query1.h>
#include <query2.h>
#include <query3.h>
#include <hashtableManager.h>
#include <cmdManager.h>

int main (int argc, char** argv){
    if (argc == 3) principal(argv[1], argv[2]); // argv[1]: data, argv[2]: cmd
    
    else {
        perror ("Wrong number of arguments");
        return 1;
    }

    return 0;
}

int principal (char* pathData, char* pathCmd) {
    hashtableManager* mngr = initializeHash ();

    getData (pathData, mngr);

    cmdManager* cmdMngr = createCmdManager ();
    int cmdNumber = readCommands (pathCmd, cmdMngr);

    for (int i = 0; i< cmdNumber; i++) {
        CMD* cmd = getCommandFromMngr (cmdMngr, i);
        
        switch (getCMDquery (cmd)) {
        case 1:
            query1 (cmd, getUserManager(mngr), i+1);
            break;

        case 2:
            query2 (cmd, mngr, i+1);
            break;

        case 3:
            query3 (cmd, getUserManager(mngr), getMusicManager(mngr), i+1);
            break;

        default:
            perror ("CMD ERROR");
            exit (EXIT_FAILURE);
        }
    }
    freeCmdManager (cmdMngr);
    freeHash (mngr);
    return 0;
}
