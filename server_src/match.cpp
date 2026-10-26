#include "match.h"

#include "../common_src/constants.h"

Match::Match(const std::string& name):
    name(name),
    received_queue(QUEUE_MAX_SIZE);
    gameloop(received_queue, clients) {
        gameloop.start();
    }

void Match::join(int client_id, Queue<WorldState>& to_send_queue) {
    clients.add_client(client_id, to_send_queue);
    received_queue.push(ClientCommand{client_id, CommandType::Join});
}

void Match::leave(int client_id) {
    clients.remove_client(client_id);
    try {
        received_queue.push(ClientCommand{client_id, CommandType::Leave});
    } catch (const ClosedQueue&) {

    }
}

void Match::push_command(const ClientCommand& cmd) {
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