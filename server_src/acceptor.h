#ifndef ACCEPTOR_H_
#define ACCEPTOR_H_

#include <list>
#include <memory>

#include "../common_src/socket.h"
#include "../common_src/thread.h"

#include "./game/command.h"

#include "client_handler.h"

class Acceptor: public Thread {
private:
    Socket skt;
    Queue<Command*>& received_queue;
    ClientQueues& client_queues;
    std::list<std::unique_ptr<ClientHandler>> clients;
    int next_client_id = 0;

    void reap_dead();

public:
    Acceptor(const char* servname, Queue<Command*>& received_queue, ClientQueues& client_queues);

    void run() override;

    ~Acceptor() override;
};

#endif
