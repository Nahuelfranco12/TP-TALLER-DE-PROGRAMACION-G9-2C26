#ifndef CLIENT_PROTOCOL_H_
#define CLIENT_PROTOCOL_H_

#include <cstdint>
#include <string>
#include <vector>

#include "../common_src/protocol.h"
#include "../common_src/socket.h"

class ClientProtocol {
private:
    Socket skt;
    Protocol protocol;

public:
    explicit ClientProtocol(const char* hostname, const char* servname);
    void send_msg(const std::string& msg);
    std::string receive_msg();
    void shutdown();
};
#endif  // CLIENT_PROTOCOL_H_
