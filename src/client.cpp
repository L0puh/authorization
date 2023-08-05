#include "src.h"
#include <cctype>

void server_connect(){
    struct addrinfo *servinfo = addr_init();
    int sockfd = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol);
    handle_err(connect(sockfd, servinfo->ai_addr, servinfo->ai_addrlen));
    freeaddrinfo(servinfo);
    log("connected");
}

void action_handle(int action) {
    User_t user;
    switch(action){
        case LOG_IN:
            user = data_get(); 
            if (repeat_password(user.password)) {
                //TODO:save user;
                log("user created");
            }
            break;
        case SIGN_IN: 
            data_get();
            break;
        default:
            logerr("unknown command");
    }
}
int action_get(){
    while(true) {
    printf("1 - log in\n2 - sign in\n");
    std::string action;
    std::getline(std::cin, action); 
    if (action.empty() || !isdigit(action[0]) ){
        logerr("action must be a number");
        continue;
    }
    return stoi(action);
    }
}
bool repeat_password(std::string psw) {
    printf("enter your password again:\n> ");
    std::string password;
    std::getline(std::cin, password);
    if (password == psw){
        return true;
    }
    return false;
}
User_t data_get() {
    User_t user;
    printf("enter your login:\n> ");
    std::getline(std::cin, user.login);

    printf("enter your password:\n> ");
    std::getline(std::cin, user.password);
    return user;
}
