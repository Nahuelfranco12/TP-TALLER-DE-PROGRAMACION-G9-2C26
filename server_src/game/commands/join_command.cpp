#include "join_command.h"

void JoinCommand::execute(World& world) {
    world.addPlayer(this->playerId, IdSector::FARM);
}