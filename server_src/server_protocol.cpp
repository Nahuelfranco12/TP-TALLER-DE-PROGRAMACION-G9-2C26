#include "server_protocol.h"

#include <cstdint>
#include <stdexcept>
#include <utility>

#include "../common_src/constants.h"
#include <sys/socket.h>

ServerProtocol::ServerProtocol(Socket &&socket)
    : skt(std::move(socket)), protocol(skt) {}

void ServerProtocol::send_sector_state(const SectorStateDto &state) {
  protocol.send_u8(OP_WORLD_STATE);

  protocol.send_u8(static_cast<uint8_t>(state.type));
  protocol.send_u16(static_cast<uint16_t>(state.width));
  protocol.send_u16(static_cast<uint16_t>(state.height));

  send_tiles(state.sector);

  protocol.send_u16(static_cast<uint16_t>(state.buildings.size()));
  for (const BuildingDto &building : state.buildings)
    send_building(building);

  protocol.send_u16(static_cast<uint16_t>(state.players.size()));
  for (const auto &[position, player] : state.players) {
    send_position(position);
    send_player(player);
  }

  protocol.send_u16(static_cast<uint16_t>(state.entities.size()));
  for (const auto &[position, entity] : state.entities) {
    send_position(position);
    protocol.send_u8(static_cast<uint8_t>(entity.type));
    protocol.send_u8(entity.ready ? 1 : 0);

    // TODO: revisar
    protocol.send_u8(static_cast<uint8_t>(entity.crop.type));
    protocol.send_u8(static_cast<uint8_t>(entity.crop.growth));
    protocol.send_u8(static_cast<uint8_t>(entity.crop.needsWater));
    protocol.send_u8(static_cast<uint8_t>(entity.mineral.remainingHits));
    protocol.send_u8(entity.enemy.alive ? 1 : 0);
    protocol.send_u8(entity.bed.sleeping ? 1 : 0);
  }

  protocol.send_u8(static_cast<uint8_t>(state.time.hours));
  protocol.send_u8(static_cast<uint8_t>(state.time.minutes));
  protocol.send_u8(static_cast<uint8_t>(state.dayNumber));
  protocol.send_u8(static_cast<uint8_t>(state.chat.size()));
  for (const ChatMessageDto &message : state.chat) {
    protocol.send_string(message.fromName);
    protocol.send_string(message.text);
    protocol.send_u8(message.isPrivate ? 1 : 0);
  }
}

void ServerProtocol::send_world_map(const WorldMapDto &map) {
  protocol.send_u8(OP_WORLD_MAP);
  protocol.send_u8(static_cast<uint8_t>(map.sectors.size()));
  for (const SectorStateDto &sector : map.sectors) {
    protocol.send_u8(static_cast<uint8_t>(sector.type));
    protocol.send_u16(static_cast<uint16_t>(sector.width));
    protocol.send_u16(static_cast<uint16_t>(sector.height));
    send_tiles(sector.sector);
    protocol.send_u16(static_cast<uint16_t>(sector.buildings.size()));
    for (const BuildingDto &building : sector.buildings)
      send_building(building);
  }
}

void ServerProtocol::send_tiles(
    const std::vector<std::vector<TileDto>> &tiles) {
  int columns = tiles.size();
  int rows = columns > 0 ? tiles[0].size() : 0;

  protocol.send_u16(static_cast<uint16_t>(columns));
  protocol.send_u16(static_cast<uint16_t>(rows));

  for (int x = 0; x < columns; x++) {
    for (int y = 0; y < rows; y++) {
      const TileDto &tile = tiles[x][y];
      protocol.send_u8(static_cast<uint8_t>(tile.type));
      protocol.send_u8(tile.transitable ? 1 : 0);
      protocol.send_u8(tile.arable ? 1 : 0);
      protocol.send_u8(tile.isDoor ? 1 : 0);
      protocol.send_u8(tile.tilled ? 1 : 0);
    }
  }
}

void ServerProtocol::send_player(const PlayerDto &player) {
  protocol.send_u16(static_cast<uint16_t>(player.id));

  send_outfit(player.outfit);

  protocol.send_u16(static_cast<uint16_t>(player.life));
  protocol.send_u16(static_cast<uint16_t>(player.energy));
  protocol.send_u16(static_cast<uint16_t>(player.coins));
  protocol.send_u8(static_cast<uint8_t>(player.actualTool));
  protocol.send_u8(static_cast<uint8_t>(player.inventory.size()));
  for (const InventoryDto &inventory : player.inventory) {
    send_inventory(inventory);
  }
  protocol.send_u16(static_cast<uint16_t>(player.pendingGift.giverId));
  send_slot(player.pendingGift.gift);
}

void ServerProtocol::send_inventory(const InventoryDto &inventory) {
  protocol.send_u16(static_cast<uint16_t>(inventory.ownerId));

  protocol.send_u16(static_cast<uint16_t>(inventory.slots.size()));
  for (const InventorySlotDto &slot : inventory.slots) {
    send_slot(slot);
  }

  protocol.send_u16(static_cast<uint16_t>(inventory.tools.size()));
  for (ToolTypeDto tool : inventory.tools) {
    protocol.send_u8(static_cast<uint8_t>(tool));
  }
}

void ServerProtocol::send_position(const GamePositionDto &position) {
  protocol.send_u16(static_cast<uint16_t>(position.x));
  protocol.send_u16(static_cast<uint16_t>(position.y));
}

void ServerProtocol::send_building(const BuildingDto &building) {
  protocol.send_u8(static_cast<uint8_t>(building.type));
  send_position(building.topLeft);
  protocol.send_u16(static_cast<uint16_t>(building.width));
  protocol.send_u16(static_cast<uint16_t>(building.height));
  send_position(building.door);
  protocol.send_u8(static_cast<uint8_t>(building.interior));
  protocol.send_u16(static_cast<uint16_t>(building.ownerId));
}

void ServerProtocol::send_slot(const InventorySlotDto &slot) {
  protocol.send_u8(static_cast<uint8_t>(slot.item));
  protocol.send_u8(static_cast<uint8_t>(slot.quality));
  protocol.send_u16(static_cast<uint16_t>(slot.count));
}

InventorySlotDto ServerProtocol::receive_slot() {
  InventorySlotDto slot;
  slot.item = static_cast<ItemTypeDto>(protocol.receive_u8());
  slot.quality = static_cast<CropQualityDto>(protocol.receive_u8());
  slot.count = protocol.receive_u16();
  return slot;
}

void ServerProtocol::shutdown() {
  try {
    skt.shutdown(SHUT_RDWR);
  } catch (const std::exception &) {
  }
}

void ServerProtocol::close() {
  shutdown();
  try {
    skt.close();
  } catch (const std::exception &) {
  }
}

MoveDto ServerProtocol::receive_move() {
  return MoveDto{byte_to_direction(protocol.receive_u8())};
}

ToolTypeDto ServerProtocol::receive_select_tool() {
  return static_cast<ToolTypeDto>(protocol.receive_u8());
}

MineDto ServerProtocol::receive_mine() {
  return MineDto{byte_to_direction(protocol.receive_u8())};
}

CollectDto ServerProtocol::receive_collect() {
  return CollectDto{byte_to_direction(protocol.receive_u8())};
}

PlantDto ServerProtocol::receive_plant() {
  PlantDto dto;
  dto.target.x = protocol.receive_u16();
  dto.target.y = protocol.receive_u16();
  dto.crop = static_cast<CropTypeDto>(protocol.receive_u8());
  return dto;
}

GiftOfferDto ServerProtocol::receive_gift_offer() {
  GiftOfferDto dto;
  dto.receiverId = protocol.receive_u16();
  dto.slotIndex = protocol.receive_u8();
  return dto;
}

GiftResponseDto ServerProtocol::receive_gift_response() {
  GiftResponseDto dto;
  dto.accept = protocol.receive_u8() == 1;
  return dto;
}

TillDto ServerProtocol::receive_till() {
  return TillDto{byte_to_direction(protocol.receive_u8())};
}

WaterDto ServerProtocol::receive_water() {
  return WaterDto{byte_to_direction(protocol.receive_u8())};
}

AttackDto ServerProtocol::receive_attack() {
  return AttackDto{byte_to_direction(protocol.receive_u8())};
}

InteractDto ServerProtocol::receive_interact() {
  InteractDto dto;
  dto.target.x = protocol.receive_u16();
  dto.target.y = protocol.receive_u16();
  return dto;
}

PlaceDto ServerProtocol::receive_place() {
  PlaceDto dto;
  dto.slotIndex = protocol.receive_u8();
  dto.direction = byte_to_direction(protocol.receive_u8());
  return dto;
}

WaterDto ServerProtocol::receive_cheat_water() {
  return WaterDto{byte_to_direction(protocol.receive_u8())};
}

ChatDto ServerProtocol::receive_chat() {
  ChatDto dto;
  dto.text = protocol.receive_string();
  return dto;
}

DirectionDto ServerProtocol::byte_to_direction(uint8_t direction_byte) {
  switch (direction_byte) {
  case DIR_UP:
    return DirectionDto::Up;
  case DIR_DOWN:
    return DirectionDto::Down;
  case DIR_LEFT:
    return DirectionDto::Left;
  case DIR_RIGHT:
    return DirectionDto::Right;
  default:
    throw std::runtime_error("Direccion inválida");
  }
}

LobbyRequestDto ServerProtocol::receive_lobby_request() {
  uint8_t operation = protocol.receive_u8();

  LobbyRequestDto request;

  switch (operation) {
  case OP_CREATE_MATCH:
    request.action = LobbyActionDto::Create;
    request.match_name = protocol.receive_string();
    break;
  case OP_LIST_MATCHES:
    request.action = LobbyActionDto::List;
    break;
  case OP_JOIN_MATCH:
    request.action = LobbyActionDto::Join;
    request.code = protocol.receive_string();
    request.player_name = protocol.receive_string();
    request.player_outfit = receive_outfit();
    break;
  default:
    throw std::runtime_error("Mensaje inesperado");
  }
  return request;
}

void ServerProtocol::send_match_created(const std::string &code) {
  protocol.send_u8(OP_CREATE_MATCH);
  protocol.send_string(code);
}

void ServerProtocol::send_match_list(const std::vector<MatchInfoDto> &matches) {
  protocol.send_u8(OP_LIST_MATCHES);
  protocol.send_u16(static_cast<uint16_t>(matches.size()));
  for (const MatchInfoDto &m : matches) {
    protocol.send_string(m.code);
    protocol.send_string(m.name);
    protocol.send_u8(static_cast<uint8_t>(m.players));
  }
}

void ServerProtocol::send_join_result(bool result) {
  protocol.send_u8(OP_JOIN_MATCH);
  if (result) {
    protocol.send_u8(JOIN_SUCCESS);
  } else {
    protocol.send_u8(JOIN_FAILURE);
  }
}

void ServerProtocol::send_player_id(int id) {
  protocol.send_u8(OP_PLAYER_ID);
  protocol.send_u16(static_cast<uint16_t>(id));
}

uint8_t ServerProtocol::receive_operation() { return protocol.receive_u8(); }

PlayerOutfitDto ServerProtocol::receive_outfit() {
  PlayerOutfitDto outfit;
  outfit.hat = static_cast<PlayerHatsDto>(protocol.receive_u8());
  outfit.hair = static_cast<PlayerHairsDto>(protocol.receive_u8());
  outfit.tshirt = static_cast<PlayerTShirtsDto>(protocol.receive_u8());
  outfit.pants = static_cast<PlayerPantsDto>(protocol.receive_u8());
  return outfit;
}

void ServerProtocol::send_outfit(const PlayerOutfitDto &outfit) {
  protocol.send_u8(static_cast<uint8_t>(outfit.hat));
  protocol.send_u8(static_cast<uint8_t>(outfit.hair));
  protocol.send_u8(static_cast<uint8_t>(outfit.tshirt));
  protocol.send_u8(static_cast<uint8_t>(outfit.pants));
}
