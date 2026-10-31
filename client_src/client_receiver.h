#ifndef CLIENT_RECEIVER_H_
#define CLIENT_RECEIVER_H_

#include <string>

#include "../common_src/queue.h"
#include "../common_src/thread.h"
#include "../common_src/game_dtos.h"

#include "client_protocol.h"

class ClientReceiver: public Thread {
private:
    ClientProtocol& protocol;
    Queue<SectorStateDto>& received_queue;

public:
    ClientReceiver(ClientProtocol& protocol, Queue<SectorStateDto>& queue);

    void run() override;
};

#endif
