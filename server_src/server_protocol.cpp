#include "server_protocol.h"

#include <cstdint>
#include <stdexcept>
#include <utility>

#include <sys/socket.h>
#include "../common_src/constants.h"

ServerProtocol::ServerProtocol(Socket&& socket): skt(std::move(socket)), protocol(skt) {}

void ServerProtocol::send_sector_state(const SectorStateDto& state) {
    protocol.send_u8(OP_WORLD_STATE);

    protocol.send_u8(static_cast<uint8_t>(state.type));
    protocol.send_u16(static_cast<uint16_t>(state.width));
    protocol.send_u16(static_cast<uint16_t>(state.height));

    send_tiles(state.sector);

    protocol.send_u16(static_cast<uint16_t>(state.players.size()));
    for (const auto& [position, player] : state.players) {
        send_position(position);
        send_player(player);
    }

    protocol.send_u16(static_cast<uint16_t>(state.entities.size()));
    for (const auto& [position, type] : state.entities) {
        send_position(position);
        protocol.send_u8(static_cast<uint8_t>(type));
    }
}

void ServerProtocol::send_tiles(const std::vector<std::vector<TileDto>>& tiles) {
    int columns = tiles.size();
    int rows = columns > 0 ? tiles[0].size() : 0;

    protocol.send_u16(static_cast<uint16_t>(columns));
    protocol.send_u16(static_cast<uint16_t>(rows));

    for (int x = 0; x < columns; x++) {
        for (int y = 0; y < rows; y++) {
            const TileDto& tile = tiles[x][y];
            protocol.send_u8(static_cast<uint8_t>(tile.type));
            protocol.send_u8(tile.transitable ? 1 : 0);
            protocol.send_u8(tile.arable ? 1 : 0);
        }
    }
}

void ServerProtocol::send_player(const PlayerDto& player) {
    protocol.send_u16(static_cast<uint16_t>(player.id));

    protocol.send_u8(static_cast<uint8_t>(player.hat));
    protocol.send_u8(static_cast<uint8_t>(player.hair));
    protocol.send_u8(static_cast<uint8_t>(player.tshirt));
    protocol.send_u8(static_cast<uint8_t>(player.pants));

    protocol.send_u16(static_cast<uint16_t>(player.life));
    protocol.send_u16(static_cast<uint16_t>(player.energy));
    protocol.send_u16(static_cast<uint16_t>(player.coins));

    protocol.send_u8(static_cast<uint8_t>(player.inventory.size()));
    for (const InventoryDto& inventory : player.inventory) {
        send_inventory(inventory);
    }
}

void ServerProtocol::send_inventory(const InventoryDto& inventory) {
    protocol.send_u16(static_cast<uint16_t>(inventory.ownerId));

    protocol.send_u16(static_cast<uint16_t>(inventory.slots.size()));
    for (const InventorySlotDto& slot : inventory.slots) {
        protocol.send_u16(static_cast<uint16_t>(slot.count));
        protocol.send_u8(static_cast<uint8_t>(slot.item));
    }

    protocol.send_u16(static_cast<uint16_t>(inventory.tools.size()));
    for (ToolTypeDto tool : inventory.tools) {
        protocol.send_u8(static_cast<uint8_t>(tool));
    }
}

void ServerProtocol::send_position(const GamePositionDto& position) {
    protocol.send_u16(static_cast<uint16_t>(position.x));
    protocol.send_u16(static_cast<uint16_t>(position.y));
}

void ServerProtocol::shutdown() {
    try {
        skt.shutdown(SHUT_RDWR);
    } catch (const std::exception&) {}
}

void ServerProtocol::close() {
    shutdown();
    try {
        skt.close();
    } catch (const std::exception&) {}
}

MoveDto ServerProtocol::receive_move() {
    return MoveDto{byte_to_direction(protocol.receive_u8())};
}

DirectionDto ServerProtocol::byte_to_direction(uint8_t direction_byte) {
    switch(direction_byte) {
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
    switch(operation) {
        case OP_CREATE_MATCH:
            return LobbyRequestDto{LobbyActionDto::Create, protocol.receive_string()};
        case OP_LIST_MATCHES:
            return LobbyRequestDto{LobbyActionDto::List, ""};
        case OP_JOIN_MATCH:
            return LobbyRequestDto{LobbyActionDto::Join, protocol.receive_string()};
        default:
            throw std::runtime_error("Mensaje inesperado");
    }
}

void ServerProtocol::send_match_created(const std::string& code) {
    protocol.send_u8(OP_CREATE_MATCH);
    protocol.send_string(code);
}

void ServerProtocol::send_match_list(const std::vector<MatchInfoDto>& matches) {
    protocol.send_u8(OP_LIST_MATCHES);
    protocol.send_u16(static_cast<uint16_t>(matches.size()));
    for(const MatchInfoDto& m : matches) {
        protocol.send_string(m.code);
        protocol.send_string(m.name);
        protocol.send_u8(static_cast<uint8_t>(m.players));
    }
}

void ServerProtocol::send_join_result(bool result){
    protocol.send_u8(OP_JOIN_MATCH);
    if(result) {
        protocol.send_u8(JOIN_SUCCESS);
    } else {
        protocol.send_u8(JOIN_FAILURE);
    }
}

void ServerProtocol::send_player_id(int id) {
    protocol.send_u8(OP_PLAYER_ID);
    protocol.send_u16(static_cast<uint16_t>(id));
}

uint8_t ServerProtocol::receive_operation() {
    return protocol.receive_u8();
}