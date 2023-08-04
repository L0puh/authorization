#include "src.h"
#include <atomic>
#include <netdb.h>
#include <sys/socket.h>

int server_init() {
    struct addrinfo *servinfo = addr_init();    
    int sockfd = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol);
    handle_err(bind(sockfd, servinfo->ai_addr, servinfo->ai_addrlen));
    freeaddrinfo(servinfo);
    handle_err(listen(sockfd, BACK_LOG));
    log("server's up");
    return sockfd;
}
struct addrinfo* addr_init(){
    struct addrinfo addr, *servinfo;
    memset(&addr, 0, sizeof(addr));
    addr.ai_family = AF_INET;
    addr.ai_socktype = SOCK_STREAM;
    addr.ai_flags = AI_PASSIVE;
    int err;
    if ((err = getaddrinfo(NULL, PORT, &addr, &servinfo)) == -1) {
        printf("[-] error in getaddrinfo: %s\n", gai_strerror(err));
        exit(1);
    }
    return servinfo;
}
void server_start(int sockfd) {
    struct sockaddr_in their_addr; 
    socklen_t their_addrlen = sizeof(their_addr);
    while(true) {
        int new_sockfd = accept(sockfd, (struct sockaddr*)&their_addr, &their_addrlen);
        log("new connection");
        std::thread th_client(handle_client, new_sockfd);
        th_client.detach();
    }
}
void handle_client(int sockfd) {

}
