#ifndef CLIENT_HANDLER_H_
#define CLIENT_HANDLER_H_

#include <functional>
#include <map>
#include <string>

#include "sender.h"
#include "receiver.h"
#include "../common_src/queue.h"
#include "../common_src/socket.h"
#include "../common_src/thread.h"

#include "server_protocol.h"

class ClientHandler {
private:
    ServerProtocol protocol;
    Queue<std::string> queue;
    Receiver receiver;
    Sender sender;
public:
    ClientHandler(Socket&& skt);

    void start();

    bool is_dead();

    ClientHandler(const ClientHandler&) = delete;
    ClientHandler& operator=(const ClientHandler&) = delete;

    ~ClientHandler();
};

#endif  // CLIENT_HANDLER_H_
