#include "spawn_mineral_command.h"
#include "../world.h"

void SpawnMineralCommand::execute(World& world) {
    world.spawnMineral(this->sectorId, this->position, this->mineralType, this->spawnFrequency, this->pickaxeTime);
}
