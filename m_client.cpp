#include "src/src.h"

int main () {
    int sockfd = server_connect();
    short action = action_get();
    User_t user = action_handle(action);
    user_send(user, sockfd, action);
    return 0;
}
