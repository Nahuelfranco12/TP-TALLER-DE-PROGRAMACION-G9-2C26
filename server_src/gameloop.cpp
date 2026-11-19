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
  this->world.addSector(
      std::make_unique<FarmSector>(SECTOR_DIMENSION_1, SECTOR_DIMENSION_2));
  this->world.addSector(
      std::make_unique<VillageSector>(SECTOR_DIMENSION_2, SECTOR_DIMENSION_1));

  world.addDoor(IdSector::FARM, IdSector::VILLAGE, Position(0, 15),
                Position(0, 15));
  
  this->world.addSector(
      std::make_unique<CommunityCenterSector>(COMMUNITY_CENTER_WIDTH, COMMUNITY_CENTER_HEIGHT));

  world.addDoor(IdSector::VILLAGE, IdSector::COMMUNITY_CENTER, Position(50, 45),
                Position(10, 11));

  this->world.spawnAnimal(IdSector::FARM, Position(10, 10), AnimalType::COW);
  this->world.spawnAnimal(IdSector::FARM, Position(11, 10),
                          AnimalType::CHICKEN);
  this->world.spawnAnimal(IdSector::FARM, Position(10, 11), AnimalType::COW);
  this->world.spawnAnimal(IdSector::FARM, Position(11, 11),
                          AnimalType::CHICKEN);

  Cavern::setup(this->world);
}

void Gameloop::run() {
  const std::chrono::milliseconds tickrate(1000 / TICKS_PER_SECOND);
  auto time_1 = std::chrono::steady_clock::now();
  try {
    while (should_keep_running()) {
      process_commands();
      world.tick();
      clients.send_to_all(make_world_state());
      world.clearChat();

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
