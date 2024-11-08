#include <cmd.h>
#include <utils.h>
#include <cmdManager.h>

typedef struct cmdmanager {
    CMD** cmdArray;
    int counter;
} cmdManager;

cmdManager* createCmdManager () {
    cmdManager* mngr = malloc (sizeof (cmdManager));
    mngr->cmdArray = NULL;
    mngr->counter = 0;
    return mngr;
}

void addCommandToManager(cmdManager* mngr, CMD* cmd) {
    CMD** temp = realloc(mngr->cmdArray, ++mngr->counter * sizeof(CMD*));
    if (temp == NULL) {
        perror("Error adding cmd to manager");
        exit(EXIT_FAILURE);
    }
    mngr->cmdArray = temp;
    mngr->cmdArray[mngr->counter - 1] = cmd;
}

void processCmdLine (char** tokens, int numberTokens, cmdManager* manager) {
    CMD* cmd = createCMD (tokens, numberTokens);
    if (cmd != NULL) addCommandToManager (manager, cmd);
}

int getCommandsCounter (cmdManager *mngr) {
    return mngr->counter;
}

CMD* getCommandFromMngr (cmdManager *mngr, int i) {
    return mngr->cmdArray [i];
}

void freeCmdManager (cmdManager *mngr) {
    if (!mngr) return;
    int counter = mngr->counter;
    for (int i = 0; i< counter; i++) {
        freeCmd (mngr->cmdArray[i]);
    }
    free (mngr->cmdArray);
    free (mngr);
}

