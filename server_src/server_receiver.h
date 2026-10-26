#ifndef SERVER_RECEIVER_H_
#define SERVER_RECEIVER_H_

#include "../common_src/queue.h"
#include "../common_src/thread.h"

#include "./game/command.h"
#include "server_protocol.h"

class ServerReceiver: public Thread {
private:
    ServerProtocol& protocol;
    Queue<Command*>& received_queue;
    int client_id;

public:
    ServerReceiver(ServerProtocol& protocol, Queue<Command*>& received_queue, int client_id);

    void run() override;
};

#endif
