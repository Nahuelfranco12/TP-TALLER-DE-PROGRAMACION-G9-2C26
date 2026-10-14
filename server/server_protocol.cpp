#include "server_protocol.h"

#include <cstdint>
#include <stdexcept>
#include <utility>

#include <arpa/inet.h>

#include "../common_src/constants.h"

ServerProtocol::ServerProtocol(Socket&& socket): skt(std::move(socket)), protocol(skt) {}

std::optional<uint8_t> ServerProtocol::receive_operation() {
    uint8_t value = 0;
    int recvd = skt.recvall(&value, 1);
    if (recvd == 0)
        return {};
    return value;
}

JoinGameDto ServerProtocol::receive_join() {
    uint8_t pet = protocol.receive_u8();
    std::string game_name = protocol.receive_string();

    return JoinGameDto{pet, game_name};
}

CreateGameDto ServerProtocol::receive_create() {
    uint8_t pet = protocol.receive_u8();
    uint8_t required = protocol.receive_u8();
    std::string game_name = protocol.receive_string();

    return CreateGameDto{pet, required, game_name};
}

void ServerProtocol::send_ret(uint8_t ret) { protocol.send_u8(ret); }

void ServerProtocol::send_game_list(const std::vector<GameListItemDto>& items) {
    protocol.send_u16(items.size());
    for (const GameListItemDto& item: items) {
        protocol.send_u8(item.current);
        protocol.send_u8(item.required);
        protocol.send_string(item.game_name);
    }
}

void ServerProtocol::close() {
    try {
        skt.shutdown(SHUT_RDWR);
    } catch (const std::exception&) {}
    try {
        skt.close();
    } catch (const std::exception&) {}
}
