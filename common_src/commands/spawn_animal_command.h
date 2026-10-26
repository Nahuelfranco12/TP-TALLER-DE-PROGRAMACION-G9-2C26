#ifndef SPAWN_ANIMAL_COMMAND_H_
#define SPAWN_ANIMAL_COMMAND_H_

#include "../command.h"
#include "../../server_src/game/entities/animal.h"
#include "../../server_src/game/id_sector.h"
#include "../../server_src/game/position.h"

class SpawnAnimalCommand : public Command {
private:
    IdSector   sectorId;
    Position   position;
    AnimalType animalType;

public:
    SpawnAnimalCommand(IdSector sectorId, Position position, AnimalType animalType)
        : sectorId(sectorId), position(position), animalType(animalType) {}

    void execute(World& world) override;
};

#endif // SPAWN_ANIMAL_COMMAND_H_
