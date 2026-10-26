#include "gameloop.h"
#include <chrono>
#include <thread>


Gameloop::Gameloop(Queue<Command*>& received_queue, ClientQueues& clients, DaySpeed worldSpeed):
    received_queue(received_queue), clients(clients), world(worldSpeed) {}

void Gameloop::run() {
    const std::chrono::milliseconds tickrate(1000 / TICKS_PER_SECOND);
    auto time_1 = std::chrono::steady_clock::now();
    try{
        while(should_keep_running()) {
            Command* cmd;
            while(received_queue.try_pop(cmd)) {
                cmd->execute(this->world);
            }
            clients.send_to_all(make_world_state());

            auto time_2 = std::chrono::steady_clock::now();
            auto rest = tickrate - (time_2 - time_1);

            if(rest < std::chrono::nanoseconds(0)) {
                auto behind = -rest;
                rest = tickrate - behind % tickrate;
                time_1 += behind + rest;
            }

            std::this_thread::sleep_for(rest);
            time_1 += tickrate;
        }
    } catch (const ClosedQueue&) {

    }
}

WorldState Gameloop::make_world_state() const {
    WorldState state;
    const std::map<int, Player*> players = world.getPlayers();

    for (const auto& [idPlayer, player] : players)
        state.players.push_back(PlayerPosition{idPlayer, player->position.x, player->position.y});
    return state;
}
