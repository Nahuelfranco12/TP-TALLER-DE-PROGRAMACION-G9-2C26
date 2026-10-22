#ifndef CLIENT_MESSAGE_H
#define CLIENT_MESSAGE_H

#include <string>

struct ClientMessage {
    int client_id = 0;
    std::string text;
}

#endif