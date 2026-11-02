#ifndef MATCH_H
#define MATCH_H

#include "../common_src/game_dtos.h"
#include "../common_src/queue.h"
#include <memory>
#include <string>

#include "./game/commands/join_command.h"
#include "./game/commands/leave_command.h"
#include "client_queues.h"
#include "gameloop.h"

class Match {
private:
  std::string name;
  Queue<std::unique_ptr<Command>> received_queue;
  ClientQueues clients;
  Gameloop gameloop;

public:
  explicit Match(const std::string &name);

  void join(int client_id, Queue<WorldState> &to_send_queue,
            std::unique_ptr<Command> join_cmd);
  void leave(int client_id);
  void push_command(std::unique_ptr<Command> cmd);
  const std::string &get_name() const;
  int player_count();

  Match(const Match &) = delete;
  Match &operator=(const Match &) = delete;

  ~Match();
};

#endif
