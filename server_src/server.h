#ifndef SERVER_H_
#define SERVER_H_

#include "acceptor.h"
#include "gameloop.h"

class Server {
private:
    Queue<ClientCommand> received_queue;
    ClientQueues client_queues;
    Gameloop gameloop;
    Acceptor acceptor;

public:
    explicit Server(const char* servname);

    void run();
};

#endif  // SERVER_H_
