#ifndef CAVERN_SECTOR_H_
#define CAVERN_SECTOR_H_

#include "sector.h"

#include <memory>
#include <random>
#include <vector>

struct CavernLevelConfig {
  size_t minMinerals;
  size_t maxMinerals;
  size_t minEnemies;
  size_t maxEnemies;
  std::vector<MineralTypes> availableMinerals;
};

class CavernSector : public Sector {
private:
  CavernLevelConfig config;
  bool pendingReset = false;
  std::mt19937 rng;

  void spawnMinerals();
  // void spawnEnemies();
  void clearEntities();
  void initEntities();
  Position randomFreePosition();

public:
  CavernSector(size_t width, size_t height, IdSector id,
               const CavernLevelConfig &config)
      : Sector(width, height, id, Terrain(true, false, TerrainType::GROUND)),
        config(config) {
    initEntities();
  }

  bool addEntity(std::unique_ptr<Entity> entity, Position pos) override;

  void reset() override;
  void endDay() override;
};

#endif // CAVERN_SECTOR_H_
