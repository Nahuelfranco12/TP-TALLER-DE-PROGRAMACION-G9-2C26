#ifndef CAVERN_SECTOR_H_
#define CAVERN_SECTOR_H_

#include "../entities/enemies/enemies_factory.h"
#include "sector.h"

#include <memory>
#include <random>
#include <vector>

struct EnemySpawnConfig {
  EnemyType type;
  size_t minGroup;
  size_t maxGroup;
  size_t maxLevel;
  size_t currentCount = 0;
};

struct CavernLevelConfig {
  size_t minMinerals;
  size_t maxMinerals;
  size_t minEnemyGroups;
  size_t maxEnemyGroups;
  std::vector<MineralTypes> availableMinerals;
  std::vector<EnemySpawnConfig> availableEnemies;
};

class CavernSector : public Sector {
private:
  CavernLevelConfig config;
  bool pendingReset = false;
  std::mt19937 rng;
  EnemiesFactory enemiesFactory;

  void spawnEnemyGroup(EnemyType type, size_t count);

  void spawnMinerals();
  void spawnEnemies();
  void spawnTraps();
  void clearEntities();
  void initEntities();
  Position randomFreePosition();
  Position randomNearPosition(Position center, int radius);

public:
  CavernSector(size_t width, size_t height, IdSector id,
               const CavernLevelConfig &config)
      : Sector(width, height, id, Terrain(true, false, TerrainType::GROUND)),
        config(config), enemiesFactory() {
    initEntities();
  }

  bool addEntity(std::unique_ptr<Entity> entity, Position pos) override;

  void reset() override;
  void endDay() override;
};

#endif // CAVERN_SECTOR_H_
