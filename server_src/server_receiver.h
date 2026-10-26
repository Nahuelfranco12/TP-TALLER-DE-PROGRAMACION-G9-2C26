#ifndef SERVER_RECEIVER_H_
#define SERVER_RECEIVER_H_

#include "../common_src/queue.h"
#include "../common_src/thread.h"

#include "server_protocol.h"
#include "match.h"

class ServerReceiver: public Thread {
private:
    ServerProtocol& protocol;
    Match& match;
    int client_id;

public:
    ServerReceiver(ServerProtocol& protocol, Match& match, int client_id);

    void run() override;
};

#endif
