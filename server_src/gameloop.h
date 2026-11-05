#ifndef GAMELOOP_H
#define GAMELOOP_H

#include <map>
#include <memory>

#include "../common_src/game_dtos.h"
#include "../common_src/queue.h"
#include "../common_src/thread.h"

#include "./game/command.h"
#include "./game/world.h"

#include "client_queues.h"

#define MAP_WIDTH 20
#define MAP_HEIGHT 20
#define START_X 10
#define START_Y 10

#define TICKS_PER_SECOND 30

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
