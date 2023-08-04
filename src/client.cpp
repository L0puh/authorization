#include "src.h"

void server_connect(){
    struct addrinfo *servinfo = addr_init();
    int sockfd = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol);
    handle_err(connect(sockfd, servinfo->ai_addr, servinfo->ai_addrlen));
    freeaddrinfo(servinfo);
    log("connected");
}
