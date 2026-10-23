#include "client.h"

#include <functional>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "../common_src/constants.h"

Client::Client(const char* hostname, const char* servname):
        protocol(hostname, servname),
        received_queue(QUEUE_MAX_SIZE),
        to_send_queue(QUEUE_MAX_SIZE),
        receiver(protocol, received_queue),
        sender(protocol, to_send_queue)
        {
            receiver.start();
            sender.start();
        }

// igual este run es de prueba, hay q sacarlo conectandolo con sdl
void Client::run() {
    std::string line;
    WorldState state;

    while(std::getline(std::cin, line) && line != "q") {
        if(!is_connected()) {
            break;
        }
        
        if(line == "w")
            send_move(Direction::Up);
        else if(line == "s")
            send_move(Direction::Down);
        else if(line == "a")
            send_move(Direction::Left);
        else if(line == "d")
            send_move(Direction::Right);

        if(try_get_latest_state(state)) {
            for(const PlayerPosition& p : state.players) {
                std::string mensaje = "Jugador " + std::to_string(p.id) + " en: " + std::to_string(p.x) + ", " + std::to_string(p.y) + STRING_BRK;
                std::cout << mensaje;
            }
        }
    }
}

void Client::send_move(Direction direction) {
    to_send_queue.try_push(MoveCommand{direction});
}

bool Client::try_get_latest_state(WorldState& state){
    bool has_been_received = false;
    WorldState next_state;
    while(received_queue.try_pop(next_state)){
        state = std::move(next_state);
        has_been_received = true;
    }
    return has_been_received;
}

bool Client::is_connected() const {
    return receiver.is_alive();
}


Client::~Client() {
    receiver.stop();
    sender.stop();
    to_send_queue.close();
    received_queue.close();
    protocol.shutdown();
    receiver.join();
    sender.join();
}