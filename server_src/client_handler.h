#ifndef CLIENT_HANDLER_H_
#define CLIENT_HANDLER_H_

#include <functional>
#include <map>

#include "../common_src/socket.h"
#include "../common_src/thread.h"

#include "server_protocol.h"

class ClientHandler: public Thread {
private:
    ServerProtocol protocol;

public:
    ClientHandler(Socket&& skt);

    void run() override;

    ~ClientHandler() override;
};

#endif  // CLIENT_HANDLER_H_
