#ifndef RECEIVER_H_
#define RECEIVER_H_

#include <string>

#include "../common_src/queue.h"
#include "../common_src/thread.h"

#include "server_protocol.h"

class Receiver: public Thread {
private:
    ServerProtocol& protocol;
    Queue<std::string>& queue;

public:
    Receiver(ServerProtocol& protocol, Queue<std::string>& queue);

    void run() override;
};

#endif  // RECEIVER_H_
