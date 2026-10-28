#ifndef SERVER_PROTOCOL_H_
#define SERVER_PROTOCOL_H_

#include <cstdint>
#include <optional>
#include <string>
#include <vector>

#include "../common_src/game_dtos.h"
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

    MoveDto receive_move();
    void send_world_state(const WorldState& state);

    void send_player_id(int id);

    LobbyRequest receive_lobby_request();
    void send_match_created(const std::string& code);
    void send_match_list(const std::vector<MatchInfo>& matches);
    void send_join_result(bool result);

    void shutdown();

    void close();
};

#endif  // SERVER_PROTOCOL_H_
