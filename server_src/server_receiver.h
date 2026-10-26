#ifndef SERVER_RECEIVER_H_
#define SERVER_RECEIVER_H_

#include "../common_src/queue.h"
#include "../common_src/thread.h"

#include "client_command.h"
#include "server_protocol.h"

class ServerReceiver: public Thread {
private:
    ServerProtocol& protocol;
    Queue<ClientCommand>& received_queue;
    int client_id;

public:
    ServerReceiver(ServerProtocol& protocol, Queue<ClientCommand>& received_queue, int client_id);

    void run() override;
};

#endif
