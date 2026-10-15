#include "receiver.h"

#include <stdexcept>
#include <iostream>

#include "../common_src/constants.h"

Receiver::Receiver(ServerProtocol& protocol, Queue<std::string>& queue):
    protocol(protocol), queue(queue) {}

void Receiver::run() {
    try {
        while(should_keep_running()) {
            std::string msg = protocol.receive_msg();
            std::cout << msg << STRING_BRK;

            if(!queue.try_push("Chau mundo")) {
                break;
            }
        }
    } catch (const ClosedQueue&) {
        
    } catch (const std::exception&) {
        
    }

    try {
        queue.close();
    } catch (const std::exception&) {

    }

    protocol.shutdown();
}