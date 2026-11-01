#include "match.h"

#include "../common_src/constants.h"

Match::Match(const std::string& name):
    name(name),
    received_queue(QUEUE_MAX_SIZE),
    gameloop(received_queue, clients) {
        gameloop.start();
    }

void Match::join(int client_id, Queue<WorldState>& to_send_queue) {
    clients.add_client(client_id, to_send_queue);
    received_queue.push(std::make_unique<JoinCommand>(client_id));
}

void Match::leave(int client_id) {
    clients.remove_client(client_id);
    try {
        received_queue.push(std::make_unique<LeaveCommand>(client_id));
    } catch (const ClosedQueue&) {
    }
}

void Match::push_command(std::unique_ptr<Command> cmd) {
    received_queue.push(cmd);
}

const std::string& Match::get_name() const {
    return name;
}

int Match::player_count() {
    return clients.size();
}

Match::~Match() {
    received_queue.close();
    gameloop.stop();
    gameloop.join();
}