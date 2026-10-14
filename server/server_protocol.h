#ifndef SERVER_PROTOCOL_H_
#define SERVER_PROTOCOL_H_

#include <cstdint>
#include <optional>
#include <string>
#include <vector>

#include "../common_src/protocol.h"
#include "../common_src/protocol_dto.h"
#include "../common_src/socket.h"

class ServerProtocol {
private:
    Socket skt;
    Protocol protocol;

public:
    explicit ServerProtocol(Socket&& socket);

    std::optional<uint8_t> receive_operation();

    JoinGameDto receive_join();
    CreateGameDto receive_create();

    void send_ret(uint8_t ret);
    void send_game_list(const std::vector<GameListItemDto>& items);

    void close();
};

#endif  // SERVER_PROTOCOL_H_
