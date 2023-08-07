#include "src.h"
#include <cstdio>

sqlite3* DB;
const char* dbfile = "clients.db";

static int callback(void *sql_data, int rows, char** data, char **colum_name){
    if (data){
        return true;
    }
    return false;
}

int db_connect(){
    int connect = sqlite3_open(dbfile, &DB);
    handle_err(connect, DB);
    log("db's up");
    return connect;
}

int table_create() {
    std::string sql = "CREATE TABLE IF NOT EXISTS\
        users(id INTEGER PRIMARY KEY AUTOINCREMENT,\
                login TEXT, password TEXT);";
    char *err; 
    handle_err(sqlite3_exec(DB, sql.c_str(), NULL, 0, &err), err);
    log("created a table");
    return 0;
}

bool user_check(User_t user) {
    std::string sql = "SELECT * FROM users WHERE login = '"\
                       + user.login + "' AND password='"\
                       + user.password + "';";
    
    bool res = sqlite3_exec(DB, sql.c_str(), callback, 0, 0);
    return res;
}

int user_save(User_t user) {
    std::string sql = "INSERT INTO users VALUES(NULL, '"\
                       + user.login + "', '" + user.password + "');";
    char *err; 
    handle_err(sqlite3_exec(DB, sql.c_str(), NULL, 0, &err), err);
    log("user saved");
    return 0;
}
void db_close() {
    sqlite3_close(DB);
    log("db's closed");
}
