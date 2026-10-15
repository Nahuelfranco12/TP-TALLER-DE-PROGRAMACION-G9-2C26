#include "sender.h"

#include <stdexcept>

Sender::Sender(ServerProtocol& protocol, Queue<std::string>& queue):
    protocol(protocol), queue(queue) {}

void Sender::run() {
    try {
        while(should_keep_running()) {
            protocol.send_msg(queue.pop());
        }
    } catch (const ClosedQueue&) {
        
    } catch (const std::exception&) {
        
    }

    protocol.shutdown();
}