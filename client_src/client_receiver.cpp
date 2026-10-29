#include "client_receiver.h"

#include <stdexcept>
#include <iostream>

#include "../common_src/constants.h"

ClientReceiver::ClientReceiver(ClientProtocol& protocol, Queue<WorldStateDto>& received_queue):
    protocol(protocol), received_queue(received_queue) {}

void ClientReceiver::run() {
    try {
        while(should_keep_running()) {
            received_queue.try_push(protocol.receive_world_state());
        }
    } catch (const ClosedQueue&) {
        
    } catch (const std::exception&) {
        
    }
}