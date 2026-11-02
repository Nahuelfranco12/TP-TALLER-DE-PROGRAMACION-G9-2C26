#include "client_protocol.h"

#include <cstdint>
#include <iostream>
#include <stdexcept>
#include <sys/socket.h>
#include <utility>

#include "../common_src/constants.h"

ClientProtocol::ClientProtocol(const char *hostname, const char *servname)
    : skt(hostname, servname), protocol(skt) {}

void ClientProtocol::shutdown() {
  try {
    skt.shutdown(SHUT_RDWR);
  } catch (const std::exception &) {
  }
}

void ClientProtocol::send_move_dto(const MoveDto &dto) {
  protocol.send_u8(OP_MOVE);
  protocol.send_u8(direction_to_byte(dto.direction));
}

uint8_t ClientProtocol::direction_to_byte(DirectionDto direction) {
  switch (direction) {
  case DirectionDto::Up:
    return DIR_UP;
  case DirectionDto::Down:
    return DIR_DOWN;
  case DirectionDto::Left:
    return DIR_LEFT;
  case DirectionDto::Right:
    return DIR_RIGHT;
  default:
    throw std::runtime_error("Dirección inválida");
  }
}

void ClientProtocol::send_select_tool(const ToolTypeDto &dto) {
  protocol.send_u8(OP_SELECT_TOOL);
  protocol.send_u8(static_cast<uint8_t>(dto));
}

void ClientProtocol::send_mine_dto(const MineDto& dto) {
  protocol.send_u8(OP_MINE);
  protocol.send_u8(direction_to_byte(dto.direction));
}

int ClientProtocol::receive_player_id() {
  if (protocol.receive_u8() != OP_PLAYER_ID)
    throw std::runtime_error("Mensaje inesperado");
  return protocol.receive_u16();
}

void ClientProtocol::send_create_match(const std::string &name) {
  protocol.send_u8(OP_CREATE_MATCH);
  protocol.send_string(name);
}

std::string ClientProtocol::receive_created_match() {
  if (protocol.receive_u8() != OP_CREATE_MATCH)
    throw std::runtime_error("Mensaje inesperado");
  return protocol.receive_string();
}

void ClientProtocol::send_list_matches() { protocol.send_u8(OP_LIST_MATCHES); }

std::vector<MatchInfoDto> ClientProtocol::receive_match_list() {
  if (protocol.receive_u8() != OP_LIST_MATCHES)
    throw std::runtime_error("Mensaje inesperado");

  std::vector<MatchInfoDto> matches;
  int count = protocol.receive_u16();
  for (int i = 0; i < count; i++) {
    MatchInfoDto matchinfo;
    matchinfo.code = protocol.receive_string();
    matchinfo.name = protocol.receive_string();
    matchinfo.players = protocol.receive_u8();
    matches.push_back(matchinfo);
  }
  return matches;
}

void ClientProtocol::send_join_match(const std::string &code,
                                     const std::string &player_name,
                                     const PlayerOutfitDto &outfit) {
  protocol.send_u8(OP_JOIN_MATCH);
  protocol.send_string(code);
  protocol.send_string(player_name);
  send_outfit(outfit);
}

void ClientProtocol::send_outfit(const PlayerOutfitDto &outfit) {
  protocol.send_u8(static_cast<uint8_t>(outfit.hat));
  protocol.send_u8(static_cast<uint8_t>(outfit.hair));
  protocol.send_u8(static_cast<uint8_t>(outfit.tshirt));
  protocol.send_u8(static_cast<uint8_t>(outfit.pants));
}

PlayerOutfitDto ClientProtocol::receive_outfit() {
  PlayerOutfitDto outfit;
  outfit.hat = static_cast<PlayerHatsDto>(protocol.receive_u8());
  outfit.hair = static_cast<PlayerHairsDto>(protocol.receive_u8());
  outfit.tshirt = static_cast<PlayerTShirtsDto>(protocol.receive_u8());
  outfit.pants = static_cast<PlayerPantsDto>(protocol.receive_u8());
  return outfit;
}

bool ClientProtocol::receive_join_result() {
  if (protocol.receive_u8() != OP_JOIN_MATCH)
    throw std::runtime_error("Mensaje inesperado");
  return protocol.receive_u8() == JOIN_SUCCESS;
}

SectorStateDto ClientProtocol::receive_sector_state() {
  if (protocol.receive_u8() != OP_WORLD_STATE)
    throw std::runtime_error(
        "Mensaje inesperado"); // este chequeo lo pongo x las dudas, lo podemos
                               // sacar mas adelante

  SectorStateDto state;
  state.type = static_cast<SectorTypeDto>(protocol.receive_u8());
  state.width = protocol.receive_u16();
  state.height = protocol.receive_u16();

  state.sector = receive_tiles();
  int player_count = protocol.receive_u16();
  for (int i = 0; i < player_count; i++) {
    GamePositionDto position = receive_position();
    state.players[position] = receive_player();
  }
  int entity_count = protocol.receive_u16();
  for (int i = 0; i < entity_count; i++) {
    GamePositionDto position = receive_position();
    state.entities[position] =
        static_cast<EntityTypeDto>(protocol.receive_u8());
  }

  return state;
}

SectorStateDto ClientProtocol::receive_sector_map_state() {
  if (protocol.receive_u8() != OP_WORLD_STATE)
    throw std::runtime_error(
        "Mensaje inesperado"); // este chequeo lo pongo x las dudas, lo podemos
                               // sacar mas adelante

  SectorStateDto state;
  state.type = static_cast<SectorTypeDto>(protocol.receive_u8());
  state.width = protocol.receive_u16();
  state.height = protocol.receive_u16();

  state.sector = receive_tiles();

  return state;
}

std::vector<std::vector<TileDto>> ClientProtocol::receive_tiles() {
  int columns = protocol.receive_u16();
  int rows = protocol.receive_u16();

  std::vector<std::vector<TileDto>> tiles(columns, std::vector<TileDto>(rows));
  for (int x = 0; x < columns; x++) {
    for (int y = 0; y < rows; y++) {
      TileDto &tile = tiles[x][y];
      tile.type = static_cast<TerrainTypeDto>(protocol.receive_u8());
      tile.transitable = protocol.receive_u8() == 1;
      tile.arable = protocol.receive_u8() == 1;
    }
  }
  return tiles;
}

PlayerDto ClientProtocol::receive_player() {
  PlayerDto player;
  player.id = protocol.receive_u16();

  player.outfit = receive_outfit();

  player.life = protocol.receive_u16();
  player.energy = protocol.receive_u16();
  player.coins = protocol.receive_u16();
  player.actualTool = static_cast<ToolTypeDto>(protocol.receive_u8());

  int inventory_count = protocol.receive_u8();
  for (int i = 0; i < inventory_count; i++) {
    player.inventory.push_back(receive_inventory());
  }
  return player;
}

InventoryDto ClientProtocol::receive_inventory() {
  InventoryDto inventory;
  inventory.ownerId = protocol.receive_u16();

  int slot_count = protocol.receive_u16();
  for (int i = 0; i < slot_count; i++) {
    InventorySlotDto slot;
    slot.count = protocol.receive_u16();
    slot.item = static_cast<ItemTypeDto>(protocol.receive_u8());
    inventory.slots.push_back(slot);
  }

  int tool_count = protocol.receive_u16();
  for (int i = 0; i < tool_count; i++) {
    inventory.tools.push_back(static_cast<ToolTypeDto>(protocol.receive_u8()));
  }
  return inventory;
}

GamePositionDto ClientProtocol::receive_position() {
  GamePositionDto position;
  position.x = protocol.receive_u16();
  position.y = protocol.receive_u16();
  return position;
}
