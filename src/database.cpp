#include "src.h"

sqlite3* DB;
const char* dbfile = "clients.db";

int db_connect(){
    int connect = sqlite3_open(dbfile, &DB);
    handle_err(connect, DB);
    log("db's up");
    return connect;
}

