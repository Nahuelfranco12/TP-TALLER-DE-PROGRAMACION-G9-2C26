#ifndef SERVER_PROTOCOL_H_
#define SERVER_PROTOCOL_H_

#include <cstdint>
#include <optional>
#include <string>
#include <vector>

#include "../common_src/game_dtos.h"
#include "../common_src/protocol.h"
#include "../common_src/socket.h"
#include "world_state.h"

class ServerProtocol {
private:
    Socket skt;
    Protocol protocol;

    DirectionDto byte_to_direction(uint8_t direction_byte);
    void send_player(const PlayerState& player);
    void send_inventory(const InventoryState& inventory);
    void send_sector(const SectorState& sector);
    void send_entity(const EntityState& entity);
    void send_position(const Position& position);

public:
    explicit ServerProtocol(Socket&& socket);
    void send_player_id(int id);

    // Recibe un número OP (Determina la acción indicada por el cliente)
    uint8_t receive_operation();

    // Protocolo de estado del mundo
    void send_world_state(const WorldState& state);

    // Protocolo de acciones
    MoveDto receive_move();

    // Protocolo de menú
    LobbyRequestDto receive_lobby_request();
    void send_match_created(const std::string& code);
    void send_match_list(const std::vector<MatchInfoDto>& matches);
    void send_join_result(bool result);

    void shutdown();

    void close();
};

#endif  // SERVER_PROTOCOL_H_
