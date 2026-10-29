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
    int receive_player_id();
    
    // Protocolo de estado del mundo
    WorldState receive_world_state();

    // Protocolo de acciones del jugador
    void send_move_dto(const MoveDto& dto);
    
    // Protocolo de menú
    void send_create_match(const std::string& name);
    void send_list_matches();
    void send_join_match(const std::string& code);
    std::string receive_created_match();
    std::vector<MatchInfo> receive_match_list();
    bool receive_join_result();

    void shutdown();
};
#endif  // CLIENT_PROTOCOL_H_
