#ifndef GAMELOOP_H
#define GAMELOOP_H

#include <map>
#include <memory>

#include "../common_src/game_dtos.h"
#include "../common_src/queue.h"
#include "../common_src/thread.h"

#include "./game/command.h"
#include "./game/world.h"

#include "./game/game_constants.h"
#include "client_queues.h"

class Gameloop : public Thread {
private:
  Queue<std::unique_ptr<Command>> &received_queue;
  ClientQueues &clients;
  World world;

  WorldState make_world_state() const;
  void process_commands();

  void addWorldSectors();

public:
  Gameloop(Queue<std::unique_ptr<Command>> &received_queue,
           ClientQueues &clients, DaySpeed worldSpeed);

  void run() override;
};

#endif
