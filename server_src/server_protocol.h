#ifndef SERVER_PROTOCOL_H_
#define SERVER_PROTOCOL_H_

#include <cstdint>
#include <string>
#include <vector>

#include "../common_src/game_dtos.h"
#include "../common_src/protocol.h"
#include "../common_src/socket.h"

class ServerProtocol {
private:
  Socket skt;
  Protocol protocol;

  static DirectionDto byte_to_direction(uint8_t direction_byte);
  void send_tiles(const std::vector<std::vector<TileDto>> &tiles);
  void send_player(const PlayerDto &player);
  void send_inventory(const InventoryDto &inventory);
  void send_position(const GamePositionDto &position);

  PlayerOutfitDto receive_outfit();
  void send_outfit(const PlayerOutfitDto &outfit);

public:
  explicit ServerProtocol(Socket &&socket);
  void send_player_id(int id);

  // Recibe un número OP (Determina la acción indicada por el cliente)
  uint8_t receive_operation();

  // Protocolo de acciones
  MoveDto receive_move();

  // Protocolo de menú
  LobbyRequestDto receive_lobby_request();
  void send_match_created(const std::string &code);
  void send_match_list(const std::vector<MatchInfoDto> &matches);
  void send_join_result(bool result);

  void send_sector_state(const SectorStateDto &state);
  void shutdown();

  void close();
};

#endif // SERVER_PROTOCOL_H_
