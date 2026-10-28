#include "client_protocol.h"

#include <cstdint>
#include <stdexcept>
#include <utility>
#include <iostream>
#include <sys/socket.h>

#include "../common_src/constants.h"

ClientProtocol::ClientProtocol(const char* hostname, const char* servname):
        skt(hostname, servname), protocol(skt) {}

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

int ClientProtocol::receive_player_id() {
    if (protocol.receive_u8() != OP_PLAYER_ID)
        throw std::runtime_error("Mensaje inesperado");
    return protocol.receive_u16();
}

void  ClientProtocol::send_create_match(const std::string& name) {
    protocol.send_u8(OP_CREATE_MATCH);
    protocol.send_string(name);
}

std::string ClientProtocol::receive_created_match() {
    if (protocol.receive_u8() != OP_CREATE_MATCH)
        throw std::runtime_error("Mensaje inesperado");
    return protocol.receive_string();
}

void ClientProtocol::send_list_matches() {
    protocol.send_u8(OP_LIST_MATCHES);
}

std::vector<MatchInfo> ClientProtocol::receive_match_list() {
    if (protocol.receive_u8() != OP_LIST_MATCHES)
        throw std::runtime_error("Mensaje inesperado");

    std::vector<MatchInfo> matches;
    int count = protocol.receive_u16();
    for (int i = 0; i < count; i++) {
        MatchInfo matchinfo;
        matchinfo.code = protocol.receive_string();
        matchinfo.name = protocol.receive_string();
        matchinfo.players = protocol.receive_u8();
        matches.push_back(matchinfo);
    }
    return matches;
}

void ClientProtocol::send_join_match(const std::string& code) {
    protocol.send_u8(OP_JOIN_MATCH);
    protocol.send_string(code);
}

bool ClientProtocol::receive_join_result() {
    if (protocol.receive_u8() != OP_JOIN_MATCH)
        throw std::runtime_error("Mensaje inesperado");
    return protocol.receive_u8() == JOIN_SUCCESS;
}
