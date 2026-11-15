#include "join_command.h"

void JoinCommand::execute(World &world) {
  world.addPlayer(this->playerId, this->name, this->outfit, IdSector::FARM);
}
