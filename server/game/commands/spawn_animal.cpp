#include "spawn_animal_command.h"
#include "../world.h"

void SpawnAnimalCommand::execute(World& world) {
    world.spawnAnimal(this->sectorId, this->position, this->animalType);
}
