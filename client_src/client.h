#ifndef CLIENT_H_
#define CLIENT_H_

#include <string>

#include "../common_src/constants.h"
#include "../common_src/queue.h"
#include "client_receiver.h"
#include "client_sender.h"
#include "client_protocol.h"

class Client {
private:
    ClientProtocol protocol;
    Queue<std::string> received_queue;
    Queue<std::string> to_send_queue;
    ClientReceiver receiver;
    ClientSender sender;

public:
    explicit Client(const char* hostname, const char* servname);

    void run();

    ~Client();
};

#endif  // CLIENT_H_
