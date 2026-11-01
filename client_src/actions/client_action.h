#ifndef CLIENT_ACTION_H_
#define CLIENT_ACTION_H_

#include "../client_protocol.h"

class ClientAction {
public:
    virtual void send_by(ClientProtocol& protocol) const = 0;
    virtual ~ClientAction() = default;
};

#endif