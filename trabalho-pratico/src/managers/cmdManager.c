#include <cmd.h>
#include <utils.h>
#include <cmdManager.h>
#include <parsing.h>

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

int readCommands (char* path, cmdManager *mngr) {
    FILE* fp = openFile(path);
    if (fp == NULL) {
        perror("Failed to open file");
        exit (EXIT_FAILURE);
    }

    int i = 0;
    char str[DEFAULT];
    while (fgets (str, sizeof (str), fp) != NULL) {
        
        char* tokens[3];
        int count = parseCmdLine(str, tokens);

        CMD* cmd = createCMD (tokens, count);
        if (cmd != NULL) addCommandToManager(mngr, cmd);
        i++;
    }
    fclose (fp);
    mngr->counter = i;
    return i;
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

