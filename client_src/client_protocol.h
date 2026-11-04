#ifndef CLIENT_PROTOCOL_H_
#define CLIENT_PROTOCOL_H_

#include <cstdint>
#include <string>
#include <vector>

#include "../common_src/game_dtos.h"
#include "../common_src/protocol.h"
#include "../common_src/socket.h"

class ClientProtocol {
private:
  Socket skt;
  Protocol protocol;
  static uint8_t direction_to_byte(DirectionDto direction);

  std::vector<std::vector<TileDto>> receive_tiles();
  PlayerDto receive_player();
  InventoryDto receive_inventory();
  GamePositionDto receive_position();

  void send_outfit(const PlayerOutfitDto &outfit);
  PlayerOutfitDto receive_outfit();

public:
  explicit ClientProtocol(const char *hostname, const char *servname);
  int receive_player_id();

  SectorStateDto receive_sector_state();
  WorldMapDto receive_world_map();

  // Protocolo de acciones del jugador
  void send_move_dto(const MoveDto &dto);
  void send_select_tool(const ToolTypeDto &dto);
  void send_mine_dto(const MineDto &dto);

  // Protocolo de menú
  void send_create_match(const std::string &name);
  void send_list_matches();
  void send_join_match(const std::string &code, const std::string &player_name,
                       const PlayerOutfitDto &outfit);
  std::string receive_created_match();
  std::vector<MatchInfoDto> receive_match_list();
  bool receive_join_result();

  void shutdown();
};
#endif // CLIENT_PROTOCOL_H_
