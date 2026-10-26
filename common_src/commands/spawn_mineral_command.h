#ifndef SPAWN_MINERAL_COMMAND_H_
#define SPAWN_MINERAL_COMMAND_H_

#include "../command.h"
#include "../../server_src/game/id_sector.h"
#include "../../server_src/game/mineral_types.h"
#include "../../server_src/game/position.h"

class SpawnMineralCommand : public Command {
private:
    IdSector sectorId;
    Position position;
    MineralTypes mineralType;
    double spawnFrequency;
    MineralPickaxeTime pickaxeTime;

public:
    SpawnMineralCommand(IdSector sectorId, Position position,
                        MineralTypes mineralType, double spawnFrequency,
                        MineralPickaxeTime pickaxeTime)
        : sectorId(sectorId), position(position), mineralType(mineralType),
          spawnFrequency(spawnFrequency), pickaxeTime(pickaxeTime) {}

    void execute(World& world) override;
};

#endif // SPAWN_MINERAL_COMMAND_H_
