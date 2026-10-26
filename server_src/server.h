#ifndef SERVER_H_
#define SERVER_H_

#include "acceptor.h"
#include "gameloop.h"

class Server {
private:
    Match match;
    Acceptor acceptor;

public:
    explicit Server(const char* servname);

    void run();
};

#endif  // SERVER_H_
