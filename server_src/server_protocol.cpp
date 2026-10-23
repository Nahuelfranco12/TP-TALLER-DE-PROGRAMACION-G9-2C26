#include "server_protocol.h"

#include <cstdint>
#include <stdexcept>
#include <utility>

#include <sys/socket.h>
#include "../common_src/constants.h"

ServerProtocol::ServerProtocol(Socket&& socket): skt(std::move(socket)), protocol(skt) {}

void ServerProtocol::send_msg(const std::string& msg) {
    protocol.send_string(msg);
}
std::string ServerProtocol::receive_msg() {
    return protocol.receive_string();
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


MoveCommand ServerProtocol::receive_move() {
    uint8_t operation = protocol.receive_u8();
    if(operation != OP_MOVE)
        throw std::runtime_error("Mensaje inesperado");

    uint8_t direction_byte = protocol.receive_u8();
    return MoveCommand{byte_to_direction(direction_byte)};
}

void ServerProtocol::send_world_state(const WorldState& state) {
    protocol.send_u8(OP_WORLD_STATE);
    protocol.send_u16(static_cast<uint16_t>(state.players.size()));
    for(const PlayerPosition& p : state.players) {
        protocol.send_u16(static_cast<uint16_t>(p.id));
        protocol.send_u16(static_cast<uint16_t>(p.x));
        protocol.send_u16(static_cast<uint16_t>(p.y));
    }
}

Direction ServerProtocol::byte_to_direction(uint8_t direction_byte) {
    switch(direction_byte) {
        case DIR_UP:
            return Direction::Up;
        case DIR_DOWN:
            return Direction::Down;
        case DIR_LEFT:
            return Direction::Left;
        case DIR_RIGHT:
            return Direction::Right;
        default:
            throw std::runtime_error("Direccion inválida");
        
    }
}