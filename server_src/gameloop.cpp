#include "gameloop.h"

Gameloop::Gameloop(Queue<ClientCommand>& received_queue, ClientQueues& clients):
    received_queue(received_queue), clients(clients) {}

void Gameloop::run() {
    while(should_keep_running()) {
        ClientCommand cmd;
        while(received_queue.try_pop(cmd)) {
            apply_cmd(cmd);
        }

        clients.send_to_all(make_world_state());
    }
}

void Gameloop::move(int client_id, Direction direction) {
    auto map_iterator = positions.find(client_id);
    if(map_iterator == positions.end())
        return;

    Position new_position = map_iterator->second;
    switch (direction) {
        case Direction::Up:
            new_position.y -= 1; break;
        case Direction::Down:
            new_position.y += 1; break;
        case Direction::Left:
            new_position.x -= 1; break;
        case Direction::Right:
            new_position.x += 1; break;
    }

    bool valid_position = new_position.x >= 0 && new_position.x < MAP_WIDTH && new_position.y >= 0 && new_position.y < MAP_HEIGHT;

    if(valid_position)
        map_iterator->second = new_position;
}

WorldState Gameloop::make_world_state() const {
    WorldState state;
    for (const auto& [client_id, pos] : positions)
        state.players.push_back(PlayerPosition{client_id, pos.x, pos.y});
    return state;
}

void Gameloop::apply_cmd(const ClientCommand& cmd) {
    switch(cmd.type) {
        case CommandType::Join:
            positions[cmd.client_id] = Position{START_X, START_Y};
            break;
        case CommandType::Leave:
            positions.erase(cmd.client_id);
            break;
        case CommandType::Move:
            move(cmd.client_id, cmd.direction);
            break;
    }
}