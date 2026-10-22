#include "client_queues.h"

void ClientQueues::add_client(int client_id, Queue<std::string>& queue) {
    std::lock_guard<std::mutex> lock(mutex);
    queues[client_id] = &queue;
}

void ClientQueues::remove_client(int client_id) {
    std::lock_guard<std::mutex> lock(mutex);
    queues.erase(client_id);
}

void ClientQueues::send_to_all(const std::string& msg){
    std::lock_guard<std::mutex> lock(mutex);
    for(auto& [id, queue] : queues) {
        try {
            queue->try_push(msg);
        } catch (const ClosedQueue&) {}
    }
}