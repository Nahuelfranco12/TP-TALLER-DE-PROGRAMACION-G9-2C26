#include "client_queues.h"

void ClientQueues::add_client(int client_id, Queue<WorldState>& queue) {
    std::lock_guard<std::mutex> lock(mutex);
    queues[client_id] = &queue;
}

void ClientQueues::remove_client(int client_id) {
    std::lock_guard<std::mutex> lock(mutex);
    queues.erase(client_id);
}

void ClientQueues::send_to_all(const WorldState& msg){
    std::lock_guard<std::mutex> lock(mutex);
    for(auto& [id, queue] : queues) {
        try {
            queue->try_push(msg);
        } catch (const ClosedQueue&) {}
    }
}

int ClientQueues::size() {
    std::lock_guard<std::mutex> lock(mutex);
    return static_cast<int>(queues.size());
}