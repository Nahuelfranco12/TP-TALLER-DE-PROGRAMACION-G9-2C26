#ifndef ACCEPTOR_H_
#define ACCEPTOR_H_

#include <list>
#include <memory>

#include "../common_src/socket.h"
#include "../common_src/thread.h"

#include "client_handler.h"
#include "game.h"

class Acceptor: public Thread {
private:
    Socket skt;

    std::list<std::unique_ptr<ClientHandler>> clients;

    void reap_dead();

public:
    Acceptor(const char* servname, Game& game);

    void run() override;

    ~Acceptor() override;
};

#endif  // ACCEPTOR_H_
