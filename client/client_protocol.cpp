#include "client_protocol.h"

#include <cstdint>
#include <stdexcept>
#include <utility>

#include "../common_src/constants.h"

ClientProtocol::ClientProtocol(const char* hostname, const char* servname):
        skt(hostname, servname), protocol(skt) {}
