#ifndef CLIENT_PROTOCOL_H_
#define CLIENT_PROTOCOL_H_

#include <cstdint>
#include <string>
#include <vector>

#include "../common_src/protocol.h"
#include "../common_src/protocol_dto.h"
#include "../common_src/socket.h"

class ClientProtocol {
private:
    Socket skt;
    Protocol protocol;

    GameListItemDto receive_game_list_item();

public:
    explicit ClientProtocol(const char* hostname, const char* servname);
};
#endif  // CLIENT_PROTOCOL_H_
