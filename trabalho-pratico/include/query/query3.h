#include <cmd.h>
#include <userManager.h>

#ifndef _QUERY3_H_
#define _QUERY3_H_

typedef struct {
    char* gender;
    int likes;
} Tuple;

void query3 (CMD *cmd, UserManager *u_mngr);

void iter_hash (GHashTable* userHashTable);

#endif  
