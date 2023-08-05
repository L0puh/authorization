#include "src/src.h"

int main () {
    server_connect();
    int action = action_get();
    action_handle(action);
    return 0;
}
