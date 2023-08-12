#include "src.h"
#include <cctype>
#include <string>

int server_connect(){
    struct addrinfo *servinfo = addr_init();
    int sockfd = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol);
    handle_err(connect(sockfd, servinfo->ai_addr, servinfo->ai_addrlen));
    freeaddrinfo(servinfo);
    log("connected");
    return sockfd;
}

std::string hash_password(const char *data) {
    std::string hash = SHA256(data);
    return hash;
}

void user_send(User_t user, int sockfd, short type) {
    std::string login = std::to_string(LOGIN) + user.login;
    std::string password = std::to_string(PASSWORD) + hash_password(user.password.c_str()); 
    Package_t pckg {.type = type, .login_size = login.size(), .password_size = password.size()};
    send(sockfd, &pckg, sizeof(pckg), 0);
    send(sockfd, login.c_str(), login.size(), 0);
    send(sockfd, password.c_str(), password.size(), 0);
    log("user sent");
}

User_t action_handle(int action) {
    User_t user;
    switch(action){
        case LOG_IN:
            again:
            user = user_get(); 
            if (repeat_password(user.password)) {
                log("user created");
                return user;
            }
            logerr("passwords didn't match");
            goto again;
        case SIGN_IN: 
            user = user_get();
            return user;
        default:
            logerr("unknown command");
            exit(1);
    }
    return User_t{};
}

short action_get(){
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
User_t user_get() {
    User_t user;
    printf("enter your login:\n> ");
    std::getline(std::cin, user.login);

    printf("enter your password:\n> ");
    std::getline(std::cin, user.password);
    return user;
}
