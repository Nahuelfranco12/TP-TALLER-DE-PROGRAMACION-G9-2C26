#ifndef CLIENT_H_
#define CLIENT_H_

#include <cstdint>
#include <functional>
#include <map>
#include <optional>
#include <sstream>
#include <string>

#include "../common_src/constants.h"
#include "../common_src/protocol_dto.h"

#include "client_parser.h"
#include "client_printer.h"
#include "client_protocol.h"

class Client {
private:
    ClientProtocol protocol;
    ClientPrinter printer;

public:
    explicit Client(const char* hostname, const char* servname);

    void run();
};

#endif  // CLIENT_H_
