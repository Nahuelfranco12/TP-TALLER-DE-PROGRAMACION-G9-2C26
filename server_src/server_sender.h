#ifndef SERVER_SENDER_H_
#define SERVER_SENDER_H_

#include "../common_src/game_dtos.h"
#include "../common_src/game_dtos_builder.h"
#include "../common_src/queue.h"
#include "../common_src/thread.h"
#include "world_state.h"

#include "server_protocol.h"

// TODO: revisar si la queue debe ser de WorldState o WorldStateDto
class ServerSender : public Thread {
private:
  ServerProtocol &protocol;
  Queue<WorldState> &to_send_queue;
  int client_id;
  GameDtosBuilder builder;

public:
  ServerSender(ServerProtocol &protocol, Queue<WorldState> &to_send_queue,
               int client_id);

  void run() override;
};

#endif
