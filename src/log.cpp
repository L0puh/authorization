#include "src.h"

void log(std::string msg){
    printf("[*] %s\n", msg.c_str());
}

void logerr(std::string msg){
    printf("[-] error: %s\n", msg.c_str());
}

void handle_err(int res, sqlite3 *DB){
    if (res) {
        printf("[-] error: %s\n", sqlite3_errmsg(DB));
        db_close();
        exit(1);
    }
}

void handle_err(int res){
    if (res == -1) {
        printf("[-] error: %s\n", strerror(res));
        db_close();
        exit(1);
    }
}
void handle_err(int res, char* err) {
    if (res != SQLITE_OK) {
        printf("[-] error: %s\n", err);
        db_close();
        exit(1);
    }
}
