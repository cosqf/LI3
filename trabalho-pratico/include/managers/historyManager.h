#include <history.h>
#include <queryUtils.h>
#include "output_handling/outputWriter.h"

#ifndef _HISTORYMANAGER_H_
#define _HISTORYMANAGER_H_

typedef struct historyManager HistoryManager;

void insertHistoryHash(GHashTable *hashtable, int key, History *history);

HistoryManager* initializeHashHistory ();

void freeHistory (HistoryManager* h_mngr);

void traverseHistorybyUser(HistoryManager* mngr, void (callback)(gpointer key, gpointer value, gpointer query_data), gpointer data);

int getDataHistory (char *path, HistoryManager* mngr);
int lengthHistory (HistoryManager* mngr);
int sortHistory (HistoryManager* manager, History*** hashArray);
void printHash(GHashTable* hash);

// trees

void initializeHistoryTree(HistoryManager* mngr);

gint compareDateGlib(const void* a, const void* b, gpointer user_data);

void insertInHistoryByWeeks2 (GTree* tree, Date firstDayOfWeek, GHashTable* artist);

void filterToTree (HistoryManager* mngr, GHashTable* tree);


void insertInHistoryByWeeks (HistoryManager* mngr, Date firstDayOfWeek, void* top10artistWeek);

bool historyTreeIsInitialized (HistoryManager* mngr);

void traverseTree(HistoryManager* mngr, gboolean callback(gpointer key, gpointer value, gpointer user_data), gpointer feeder);

void callbackHistory(char **tokens, void *manager, Output *output);

#endif