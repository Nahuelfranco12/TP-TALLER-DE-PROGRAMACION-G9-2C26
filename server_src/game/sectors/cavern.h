#ifndef CAVERN_H_
#define CAVERN_H_

#include "../world.h"
#include "cavern_sector.h"
#include "sector.h"

#include <memory>
#include <utility>
#include <vector>

class Cavern {
private:
  static IdSector levelId(size_t level) {
    return static_cast<IdSector>(static_cast<size_t>(IdSector::CAVERN_LEVEL_1) +
                                 level);
  }

public:
  static void setup(World &world) {
    for (size_t i = 0; i < MAX_CAVERN_LEVELS; i++) {
      std::vector<MineralTypes> minerals = {
          MineralTypes::COAL, MineralTypes::IRON, MineralTypes::LAPIZLAZULI};
      if (i >= 4)
        minerals.push_back(MineralTypes::GOLD);

      CavernLevelConfig config{.minMinerals = 8 + i * 2,
                               .maxMinerals = 12 + i * 2,
                               .minEnemyGroups = 3 + i,
                               .maxEnemyGroups = 6 + i,
                               .availableMinerals = minerals,
                               .availableEnemies = {
                                   {EnemyType::SKELETON, 1, 1},
                                   {EnemyType::ORC, 3, 3},
                                   {EnemyType::VAMPIRE_MALE, 1, 1},
                               }};
      world.addSector(std::make_unique<CavernSector>(
          CAVERN_DIMENSION, CAVERN_DIMENSION, levelId(i), config));
    }
    world.addDoor(IdSector::FARM, IdSector::CAVERN_LEVEL_1, Position(15, 0),
                  Position(15, 29));
    for (int i = 0; i < MAX_CAVERN_LEVELS - 1; i++) {
      world.addDoor(levelId(i), levelId(i + 1), Position(15, 0),
                    Position(15, 29));
    }
  }
};

#endif // CAVERN_H_
