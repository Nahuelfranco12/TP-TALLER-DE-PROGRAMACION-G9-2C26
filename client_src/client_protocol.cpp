#include "client_protocol.h"

#include <cstdint>
#include <stdexcept>
#include <utility>
#include <iostream>
#include <sys/socket.h>

#include "../common_src/constants.h"

ClientProtocol::ClientProtocol(const char* hostname, const char* servname):
        skt(hostname, servname), protocol(skt) {}

void ClientProtocol::send_msg(const std::string& msg) {
    protocol.send_string(msg);
}

std::string ClientProtocol::receive_msg() {
    return protocol.receive_string();
}

void ClientProtocol::shutdown() {
    try {
        skt.shutdown(SHUT_RDWR);
    } catch (const std::exception&) {}
}

void ClientProtocol::send_move_cmd(const MoveCommand& cmd){
    protocol.send_u8(OP_MOVE);
    protocol.send_u8(direction_to_byte(cmd.direction));
}


WorldState ClientProtocol::receive_world_state(){
    uint8_t operation = protocol.receive_u8();
    if (operation != OP_WORLD_STATE)
        throw std::runtime_error("Mensaje inesperado");

    WorldState state;
    int player_count = protocol.receive_u16();
    for (int i = 0; i < player_count; i++) {
        PlayerPosition p;
        p.id = protocol.receive_u16();
        p.x = protocol.receive_u16();
        p.y = protocol.receive_u16();
        state.players.push_back(p);
    }
    return state;
}


uint8_t ClientProtocol::direction_to_byte(Direction direction) {
    switch(direction) {
        case Direction::Up:
            return DIR_UP;
        case Direction::Down:
            return DIR_DOWN;
        case Direction::Left:
            return DIR_LEFT;
        case Direction::Right:
            return DIR_RIGHT;
        default:
            throw std::runtime_error("Dirección inválida");
    }
}
