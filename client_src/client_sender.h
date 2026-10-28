#ifndef CLIENT_SENDER_H_
#define CLIENT_SENDER_H_

#include <string>

#include "../common_src/queue.h"
#include "../common_src/thread.h"
#include "../common_src/game_dtos.h"

#include "client_protocol.h"

class ClientSender: public Thread {
private:
    ClientProtocol& protocol;
    Queue<MoveDto>& to_send_queue;

public:
    ClientSender(ClientProtocol& protocol, Queue<MoveDto>& to_send_queue);

    void run() override;
};

#endif 