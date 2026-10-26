#include "server_sender.h"

#include <stdexcept>

ServerSender::ServerSender(ServerProtocol& protocol, Queue<WorldState>& to_send_queue):
    protocol(protocol), to_send_queue(to_send_queue) {}

void ServerSender::run() {
    try {
        while(should_keep_running()) {
            protocol.send_world_state(to_send_queue.pop());
        }
    } catch (const ClosedQueue&) {
        
    } catch (const std::exception&) {
        
    }

    protocol.shutdown();
}