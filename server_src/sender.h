#ifndef SENDER_H_
#define SENDER_H_

#include <string>

#include "../common_src/queue.h"
#include "../common_src/thread.h"

#include "server_protocol.h"

class Sender: public Thread {
private:
    ServerProtocol& protocol;
    Queue<std::string>& queue;

public:
    Sender(ServerProtocol& protocol, Queue<std::string>& queue);

    void run() override;
};

#endif  // SENDER_H_    