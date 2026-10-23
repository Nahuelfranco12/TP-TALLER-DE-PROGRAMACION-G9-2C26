#ifndef CLIENT_H_
#define CLIENT_H_

#include <string>

#include "../common_src/constants.h"
#include "../common_src/game_dtos.h"
#include "../common_src/queue.h"
#include "client_receiver.h"
#include "client_sender.h"
#include "client_protocol.h"

class Client {
private:
    ClientProtocol protocol;
    Queue<WorldState> received_queue;
    Queue<MoveCommand> to_send_queue;
    ClientReceiver receiver;
    ClientSender sender;

public:
    explicit Client(const char* hostname, const char* servname);

    void send_move(Direction direction);
    bool try_get_latest_state(WorldState& state);
    bool is_connected();

    void run();

    ~Client();
};

#endif  // CLIENT_H_
