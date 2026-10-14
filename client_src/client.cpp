#include "client.h"

#include <functional>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "../common_src/constants.h"

Client::Client(const char* hostname, const char* servname):
        protocol(hostname, servname)
        {}


void Client::run() {
    protocol.send_msg();
    protocol.receive_msg();
}
