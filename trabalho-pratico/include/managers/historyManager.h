#include <history.h>
#include <queryUtils.h>
#include "output_handling/outputWriter.h"

#ifndef _HISTORYMANAGER_H_
#define _HISTORYMANAGER_H_

typedef struct historyManager HistoryManager;

void insertHistoryHash (HistoryManager *h_mngr, int key, History *history);

HistoryManager* initializeHashHistory ();

void freeHashHistory (HistoryManager* h_mngr);

int getDataHistory (char *path, HistoryManager* mngr);
int lengthHistory (HistoryManager* mngr);
History** sortHistory (HistoryManager* mngr);


void printHash(GHashTable* hash);

// trees

void initializeHistoryTree(HistoryManager* mngr);

void insertInHistoryByWeeks (HistoryManager* mngr, void* top10artistWeek, Date firstDayOfWeek);

bool historyTreeIsInitialized (HistoryManager* mngr);

void freeHistoryWeeks(HistoryManager* mngr);

void traverseTreeInRange(HistoryManager* mngr, gboolean callback(gpointer key, gpointer value, gpointer user_data), gpointer feeder);

void callbackHistory(char **tokens, void *manager, Output *output);

#endif