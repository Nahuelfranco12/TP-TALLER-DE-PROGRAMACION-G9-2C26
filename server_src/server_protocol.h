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
  void send_slot(const InventorySlotDto &slot);
  void send_position(const GamePositionDto &position);
  void send_building(const BuildingDto &building);

  PlayerOutfitDto receive_outfit();
  InventorySlotDto receive_slot(); // se usa para recibir regalos
  void send_outfit(const PlayerOutfitDto &outfit);

public:
  explicit ServerProtocol(Socket &&socket);
  void send_player_id(int id);

  // Recibe un número OP (Determina la acción indicada por el cliente)
  uint8_t receive_operation();

  // Protocolo de acciones
  MoveDto receive_move();
  MineDto receive_mine();
  ToolTypeDto receive_select_tool();
  CollectDto receive_collect();
  PlantDto receive_plant();
  GiftOfferDto receive_gift_offer();
  GiftResponseDto receive_gift_response();
  TillDto receive_till();
  WaterDto receive_water();
  AttackDto receive_attack();
  InteractDto receive_interact();
  ChatDto receive_chat();
  WaterDto receive_cheat_water();
  PlaceDto receive_place();

  // Protocolo de menú
  LobbyRequestDto receive_lobby_request();
  void send_match_created(const std::string &code);
  void send_match_list(const std::vector<MatchInfoDto> &matches);
  void send_join_result(bool result);

  void send_sector_state(const SectorStateDto &state);

  // Protocolo de mapa
  void send_world_map(const WorldMapDto &map);
  void shutdown();

  void close();
};

#endif // SERVER_PROTOCOL_H_
