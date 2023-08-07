#include "src/src.h"

int main () {
    int conn = db_connect();
    int sockfd = server_init();
    table_create();
    server_start(sockfd);
    db_close();

    return 0;
}
