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
    void shutdown();

    void send_move_cmd(const MoveCommand& cmd);

    WorldState receive_world_state();

    int receive_player_id();

    void send_create_match(const std::string& name);
    std::string receive_created_match();
    void send_list_matches();
    std::vector<MatchInfo> receive_match_list();
    void send_join_match(const std::string& code);
    bool receive_join_result();
};
#endif  // CLIENT_PROTOCOL_H_
