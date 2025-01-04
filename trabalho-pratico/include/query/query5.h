#include <almightyManager.h>
#include <cmd.h>

#ifndef _QUERY5_H_
#define _QUERY5_H_

/**
 * @brief Recommends users with similar music tastes as the given user.
 * If the matrix and user ID array have not been iniatilize yet, initializes them. Uses the function recomendaUtilizadores
 * provided by the professors to acquire the recommended users IDs.
 * 
 * @param cmd A pointer to the command struct.
 * @param h_mngr A pointer to the history manager.
 * @param m_mngr A pointer to the music manager.
 * @param u_mngr A pointer to the user manager.
 * @param counter A counter with the number of the command.  
 */
void query5 (CMD* cmd, HistoryManager* h_mngr, MusicManager* m_mngr, UserManager* u_mngr, int counter);

#endif
