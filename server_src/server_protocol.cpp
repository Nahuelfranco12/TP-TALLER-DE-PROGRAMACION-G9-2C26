#include "server_protocol.h"

#include <cstdint>
#include <stdexcept>
#include <utility>

#include <sys/socket.h>
#include "../common_src/constants.h"

ServerProtocol::ServerProtocol(Socket&& socket): skt(std::move(socket)), protocol(skt) {}


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

// TODO: revisar
void ServerProtocol::send_world_state(const WorldState& state) {
    protocol.send_u8(OP_WORLD_STATE);
    protocol.send_u16(static_cast<uint16_t>(state.players.size()));
    for(const PlayerPosition& p : state.players) {
        protocol.send_u16(static_cast<uint16_t>(p.id));
        protocol.send_u16(static_cast<uint16_t>(p.x));
        protocol.send_u16(static_cast<uint16_t>(p.y));
    }
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