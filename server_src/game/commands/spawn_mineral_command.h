#ifndef SPAWN_MINERAL_COMMAND_H_
#define SPAWN_MINERAL_COMMAND_H_

#include "../command.h"
#include "../game_constants.h"
#include "../position.h"

class SpawnMineralCommand : public Command {
private:
  IdSector sectorId;
  Position position;
  MineralTypes mineralType;
  double spawnFrequency;
  size_t pickaxeHits;

public:
  SpawnMineralCommand(IdSector sectorId, Position position,
                      MineralTypes mineralType, double spawnFrequency,
                      size_t pickaxeHits)
      : sectorId(sectorId), position(position), mineralType(mineralType),
        spawnFrequency(spawnFrequency), pickaxeHits(pickaxeHits) {}

  void execute(World &world) override;
};

#endif // SPAWN_MINERAL_COMMAND_H_
