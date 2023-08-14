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
#include <iostream>
#include <string> 
#include <vector>
#include "sha2/sha2.h"
#define PORT "9000"
#define BACK_LOG 10


enum Message_type {
    LOGIN=0,
    PASSWORD=1, 
    COMMAND=2
};
enum Types {
    LOG_IN=1,
    SIGN_IN,
    REQUEST,
    DELETE,
    UPDATE,
    SUCCESS,
    ERROR_EXISTS, 
    ERROR, 
};

struct Conn_t {
    int sockfd;
    std::string login;
};

struct Package_t { 
    short type;
    size_t login_size;
    size_t password_size;
};

struct User_t {
    std::string login;
    std::string password;
};

struct addrinfo* addr_init();
/// SERVER ///
int server_init(); 
void handle_client(int sockfd);
User_t handle_recv(int sockfd, Package_t pckg);
void handle_enter(short type, User_t user);
void server_start(int sockfd);
char* user_recv(size_t size_pckg, int sockfd);
void send_pckg(Package_t pckg, std::string login);
void conn_add(std::string login,int sockfd);

/// CLIENT ///
int server_connect();
User_t user_get();
short action_get();
User_t action_handle(int action);
void user_send(User_t user, int sockfd, short type);
bool repeat_password(std::string psw);
std::string hash_password(char *data);
void recv_pckg(int sockfd);
/// DATABASE //// 
int db_connect();
void db_close();
int table_create();
bool user_check(User_t user);
int user_save(User_t user);
static int callback(void *sql_data, int rows, char** data, char **colum_name);

/// log handle /// 
void handle_err(int res);
void handle_err(int res, sqlite3 *DB);
void handle_err(int res, char* err);
void log(std::string message);
void log(int type);
void logerr(std::string message);

#endif

