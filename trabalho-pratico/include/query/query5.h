#include <hashtableManager.h>
#include <cmd.h>

#ifndef _QUERY5_H_
#define _QUERY5_H_

void query5 (CMD* cmd, HistoryManager* h_mngr, MusicManager* m_mngr, int counter);

void updateMatrix (gpointer key, gpointer value, gpointer feeder);

int** resizeMatrix(int** matrix, int currentRows, int newRows, int cols);

void freeMatrix(int** matrix, int rows);

char** resizeUserArray(char** array, int currentRows, int newRows, int cols);

void freeUserArray(char** array, int rows);

char* formatUserID (int id);

void printMatrix(int rows, int cols, int** matrix);

#endif
