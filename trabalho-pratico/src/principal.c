#include <stdio.h>
#include <principal.h>
#include <parsingUtils.h>
#include <parsing.h>
#include <utils.h>
#include <cmd.h>

#include <query1.h>
#include <query2.h>
#include <query3.h>
#include <query4.h>
#include <query5.h>

#include <almightyManager.h>
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
    AlmightyManager* mngr = initializeHash ();

    if (getData (pathData, mngr)) return 1;

    cmdManager* cmdMngr = createCmdManager ();
    int cmdNumber = parseCmdFile (pathCmd, cmdMngr);
    if (cmdNumber == -1) {
        freeCmdManager (cmdMngr);
        freeHash (mngr);
        return 1;
    }
    for (int i = 0; i< cmdNumber; i++) {
        CMD* cmd = getCommandFromMngr (cmdMngr, i);
        
        switch (getCMDquery (cmd)) {
        case 1:
            query1 (cmd, mngr, i+1);
            break;

        case 2:
            query2 (cmd, mngr, i+1);
            break;

        case 3:
            query3 (cmd, getUserManager(mngr), getMusicManager(mngr), i+1);
            break;
            
        case 4:
            query4 (cmd, getHistoryManager (mngr), getMusicManager (mngr), getArtistManager (mngr), i+1);
            break;
        
        case 5:
            query5 (cmd, getHistoryManager(mngr), getMusicManager (mngr), getUserManager(mngr), i+1);
            break;

        case 6:
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
