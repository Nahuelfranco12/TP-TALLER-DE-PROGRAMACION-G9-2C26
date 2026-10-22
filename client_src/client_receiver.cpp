#include "client_receiver.h"

#include <stdexcept>
#include <iostream>

#include "../common_src/constants.h"

ClientReceiver::ClientReceiver(ClientProtocol& protocol, Queue<std::string>& received_queue):
    protocol(protocol), received_queue(received_queue) {}

void ClientReceiver::run() {
    try {
        while(should_keep_running()) {
            received_queue.try_push(protocol.receive_msg());
        }
    } catch (const ClosedQueue&) {
        
    } catch (const std::exception&) {
        
    }
}