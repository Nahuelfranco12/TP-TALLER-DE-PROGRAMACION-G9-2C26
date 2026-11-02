#ifndef CLIENT_SENDER_H_
#define CLIENT_SENDER_H_

#include <memory>
#include <string>

#include "../common_src/game_dtos.h"
#include "../common_src/queue.h"
#include "../common_src/thread.h"
#include "actions/client_action.h"
#include "client_protocol.h"

class ClientSender : public Thread {
private:
  ClientProtocol &protocol;
  Queue<std::unique_ptr<ClientAction>> &to_send_queue;

public:
  ClientSender(ClientProtocol &protocol,
               Queue<std::unique_ptr<ClientAction>> &to_send_queue);

  void run() override;
};

#endif
