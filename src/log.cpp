#include "src.h"

void log(std::string msg){
    printf("[*] %s\n", msg.c_str());
}

void handle_err(int res, sqlite3 *DB){
    if (res) {
        printf("[-] error: %s\n", sqlite3_errmsg(DB));
        exit(1);
    }
}

void handle_err(int res){
    if (res == -1) {
        printf("[-] error: %s\n", strerror(res));
        exit(1);
    }
}
