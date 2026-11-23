#ifndef SERVER_RECEIVER_H_
#define SERVER_RECEIVER_H_

#include "../common_src/queue.h"
#include "../common_src/thread.h"

#include "./game/command.h"
#include "command_factory.h"
#include "lobby.h"
#include "match.h"
#include "server_protocol.h"

class ServerReceiver : public Thread {
private:
  ServerProtocol &protocol;
  Lobby &lobby;
  Queue<WorldState> &to_send_queue;
  int client_id;
  Match *match = nullptr;
  CommandFactory factory;

public:
  ServerReceiver(ServerProtocol &protocol, Lobby &lobby,
                 Queue<WorldState> &to_send_queue, int client_id);

  void run() override;
};

#endif
