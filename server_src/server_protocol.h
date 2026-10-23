#ifndef SERVER_PROTOCOL_H_
#define SERVER_PROTOCOL_H_

#include <cstdint>
#include <optional>
#include <string>
#include <vector>

#include "../common_src/constants.h"
#include "../common_src/protocol.h"
#include "../common_src/socket.h"
#include "../common_src/game_dtos.h"

class ServerProtocol {
private:
    Socket skt;
    Protocol protocol;

    Direction byte_to_direction(uint8_t direction_byte);

public:
    explicit ServerProtocol(Socket&& socket);

    MoveCommand receive_move();
    void send_world_state(const WorldState& state);

    void shutdown();

    void close();


};

#endif  // SERVER_PROTOCOL_H_
