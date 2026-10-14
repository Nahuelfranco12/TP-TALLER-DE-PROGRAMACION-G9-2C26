#ifndef SERVER_PROTOCOL_H_
#define SERVER_PROTOCOL_H_

#include <cstdint>
#include <optional>
#include <string>
#include <vector>

#include "../common_src/protocol.h"
#include "../common_src/socket.h"

class ServerProtocol {
private:
    Socket skt;
    Protocol protocol;

public:
    explicit ServerProtocol(Socket&& socket);

    void send_msg();
    void receive_msg();

    void close();
};

#endif  // SERVER_PROTOCOL_H_
