#ifndef SERVER_RECEIVER_H_
#define SERVER_RECEIVER_H_

#include "../common_src/queue.h"
#include "../common_src/thread.h"

#include "server_protocol.h"
#include "match.h"

class ServerReceiver: public Thread {
private:
    ServerProtocol& protocol;
    Lobby& lobby;
    Queue<WorldState>& to_send_queue;
    int client_id;
    Match* match = nullptr;

public:
    ServerReceiver(ServerProtocol& protocol, Lobby& lobby, Queue<WorldState>& to_send_queue, int client_id);

    void run() override;
};

#endif
