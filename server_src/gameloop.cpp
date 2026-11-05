#include "gameloop.h"
#include <chrono>
#include <memory>
#include <thread>

Gameloop::Gameloop(Queue<std::unique_ptr<Command>> &received_queue,
                   ClientQueues &clients, DaySpeed worldSpeed)
    : received_queue(received_queue), clients(clients), world(worldSpeed) {
      addWorldSectors();
}

void Gameloop::process_commands() {
  std::unique_ptr<Command> cmd;
  while (received_queue.try_pop(cmd)) {
    cmd->execute(this->world);
  }
}

void Gameloop::addWorldSectors() {
  this->world.addSector(IdSector::FARM);
  this->world.addSector(IdSector::CAVERN_LEVEL);
  this->world.addSector(IdSector::VILLAGE);

  this->world.addDoor(IdSector::FARM, IdSector::CAVERN_LEVEL, Position(15, 0), Position(15, 0));
  this->world.addDoor(IdSector::FARM, IdSector::VILLAGE, Position(0, 15), Position(0, 15));
}


void Gameloop::run() {
  const std::chrono::milliseconds tickrate(1000 / TICKS_PER_SECOND);
  auto time_1 = std::chrono::steady_clock::now();
  try {
    while (should_keep_running()) {
      process_commands();
      world.tick();
      clients.send_to_all(make_world_state());

      auto time_2 = std::chrono::steady_clock::now();
      auto rest = tickrate - (time_2 - time_1);

      if (rest < std::chrono::nanoseconds(0)) {
        auto behind = -rest;
        rest = tickrate - behind % tickrate;
        time_1 += behind + rest;
      }

      std::this_thread::sleep_for(rest);
      time_1 += tickrate;
    }
  } catch (const ClosedQueue &) {
  }
}

WorldState Gameloop::make_world_state() const { return world.state(); }
