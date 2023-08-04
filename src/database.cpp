#include "src.h"

sqlite3* DB;
const char* dbfile = "clients.db";

int db_connect(){
    int connect = sqlite3_open(dbfile, &DB);
    handle_err(connect, DB);
    return 0;

}

void handle_err(int res, sqlite3 *DB){
    if (res) {
        printf("[-] error: %s\n", sqlite3_errmsg(DB));
        exit(1);
    }
}

