#ifndef SERVER_H_
#define SERVER_H_

#include "acceptor.h"
#include "game.h"

class Server {
private:
    const char* servname;
    Game& game;
    Acceptor acceptor;

public:
    Server(const char* servname, Game& game);

    void run();
};

#endif  // SERVER_H_
