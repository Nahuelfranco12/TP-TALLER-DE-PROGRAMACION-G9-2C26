#include "client.h"

#include <functional>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "../common_src/constants.h"

Client::Client(const char* hostname, const char* servname):
        protocol(hostname, servname),
        received_queue(QUEUE_MAX_SIZE),
        to_send_queue(QUEUE_MAX_SIZE),
        receiver(protocol, received_queue),
        sender(protocol, to_send_queue)
        {
            receiver.start();
            sender.start();
        }


void Client::run() {
    std::string line;
    while(std::getline(std::cin, line) && line != "q") {
        if(!receiver.is_alive()) {
            break;
        }
        to_send_queue.push(line);

        std::string msg;
        while(received_queue.try_pop(msg))
            std::cout << msg << STRING_BRK;
    }
}


Client::~Client() {
    receiver.stop();
    sender.stop();
    to_send_queue.close();
    received_queue.close();
    protocol.shutdown();
    receiver.join();
    sender.join();
}