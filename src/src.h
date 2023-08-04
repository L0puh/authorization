#ifndef SRC_H
#define SRC_H

#include <stdlib.h>
#include <stdio.h>
#include "sqlite3.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>


/// DATABASE //// 
void handle_err(int res, sqlite3 *DB);
int db_connect();


#endif

