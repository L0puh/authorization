#include "src/src.h"

int main () {
    int conn = db_connect();
    int sockfd = server_init();
    server_start(sockfd);
    return 0;
}
