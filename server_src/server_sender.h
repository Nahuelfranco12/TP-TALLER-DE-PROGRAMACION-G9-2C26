#ifndef SERVER_SENDER_H_
#define SERVER_SENDER_H_

#include "../common_src/game_dtos.h"
#include "../common_src/queue.h"
#include "../common_src/thread.h"

#include "server_protocol.h"

class ServerSender: public Thread {
private:
    ServerProtocol& protocol;
    Queue<WorldState>& to_send_queue;

public:
    ServerSender(ServerProtocol& protocol, Queue<WorldState>& to_send_queue);

    void run() override;
};

#endif  