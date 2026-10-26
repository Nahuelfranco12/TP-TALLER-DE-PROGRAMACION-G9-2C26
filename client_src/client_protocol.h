#ifndef CLIENT_PROTOCOL_H_
#define CLIENT_PROTOCOL_H_

#include <cstdint>
#include <string>
#include <vector>

#include "../common_src/protocol.h"
#include "../common_src/socket.h"
#include "../common_src/game_dtos.h"

class ClientProtocol {
private:
    Socket skt;
    Protocol protocol;
    uint8_t direction_to_byte(Direction direction);
    
public:
    explicit ClientProtocol(const char* hostname, const char* servname);
    void send_msg(const std::string& msg);
    std::string receive_msg();
    void shutdown();

    void send_move_cmd(const MoveCmd& cmd);

    WorldState receive_world_state();
};
#endif  // CLIENT_PROTOCOL_H_
