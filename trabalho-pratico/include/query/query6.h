#include <almightyManager.h>
#include <cmd.h>
#include <historyManager.h>

#ifndef _QUERY6_H_
#define _QUERY6_H_

void query6(CMD* cmd, HistoryManager* h_mngr, MusicManager* m_mngr, int cmdCounter);

Duration calculateListenTime (History* history, Duration listenTime);


#endif