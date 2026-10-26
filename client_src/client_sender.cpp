#include "client_sender.h"

#include <stdexcept>

ClientSender::ClientSender(ClientProtocol& protocol, Queue<MoveCmd>& to_send_queue):
    protocol(protocol), to_send_queue(to_send_queue) {}

void ClientSender::run() {
    try {
        while(should_keep_running()) {
            protocol.send_move_cmd(to_send_queue.pop());
        }
    } catch (const ClosedQueue&) {
        
    } catch (const std::exception&) {
        
    }

    protocol.shutdown();
}