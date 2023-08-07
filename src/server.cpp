#include "src.h"
#include <atomic>
#include <cstring>
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

void handle_enter(short type, User_t user){
    //TODO:send back to client 
    bool exists = user_check(user);
    if (!exists) {
        user_save(user);
    } else if (type == SIGN_IN && exists) {
        log("log in success");
    } 
    else logerr("the user exists");
}
void handle_client(int sockfd) {
    Package_t pckg;
    User_t user;
    int bytes;     
    while ((bytes = recv(sockfd, &pckg, sizeof(pckg), 0)) > 0){
        switch(pckg.type) {
            case SIGN_IN:
            case LOG_IN:
                user = handle_recv(sockfd, pckg);
                user.login.erase(0, 1);
                handle_enter(pckg.type, user);
                break;
            default:
                logerr("unknown type");
        }
    } 
    if (bytes == 0) {
        log("user's out");
    }
}
User_t handle_recv(int sockfd, Package_t pckg){
    char* login = user_recv(pckg.login_size, sockfd);
    int type = login[0] - '0';
    User_t user;
    if (type == LOGIN) {
        user.login = login;
        char* password = user_recv(pckg.password_size, sockfd);
        type = password[0] - '0';
        if (type  == PASSWORD) user.password = password;
        delete[] login;
        delete[] password;
    }
    return user; 
}

char* user_recv(size_t size_pckg, int sockfd){
    char *message = new char[size_pckg + 1];
    message[size_pckg] = '\0';
    recv(sockfd, message, size_pckg, 0);
    return message;
}

