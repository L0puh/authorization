#ifndef SRC_H
#define SRC_H

#include <stdlib.h>
#include <stdio.h>
#include "sqlite3.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <cstring>
#include <string>
#include <thread>
#define PORT "9000"
#define BACK_LOG 10

struct addrinfo* addr_init();

/// SERVER ///
int server_init(); 
void handle_client(int sockfd);
void server_start(int sockfd);

/// CLIENT ///
void server_connect();

/// DATABASE //// 
int db_connect();

/// log handle /// 
void handle_err(int res);
void handle_err(int res, sqlite3 *DB);
void log(std::string message);

#endif

