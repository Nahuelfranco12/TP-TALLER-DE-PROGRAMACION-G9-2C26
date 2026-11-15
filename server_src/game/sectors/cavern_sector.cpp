#include "cavern_sector.h"

#include "../entities/mineral.h"
#include "../entities/skeleton.h"

#include <memory>
#include <random>
#include <utility>
#include <algorithm>

bool CavernSector::addEntity(std::unique_ptr<Entity> entity, Position pos) {
    if (entity->getType() == EntityTypes::PLAYER && playerCount() == 0)
        reset();

    if (entity->getType() == EntityTypes::PLAYER && !isEmpty(pos)) {
        pos = randomFreePosition();
    }

    return Sector::addEntity(std::move(entity), pos);
}

void CavernSector::initEntities() {
  spawnMinerals();
  spawnEnemies();
}

void CavernSector::reset() {
  clearEntities();
  initEntities();
  pendingReset = false;
}

void CavernSector::endDay() {
  if (playerCount() == 0)
    reset();
  else
    pendingReset = true;
}

void CavernSector::clearEntities() {
  auto it = entities.begin();
  while (it != entities.end()) {
    EntityTypes type = it->second->getType();
    if (type != EntityTypes::PLAYER)
      it = entities.erase(it);
    else
      it++;
  }
}

void CavernSector::spawnMinerals() {
  std::uniform_int_distribution<int> countDist(config.minMinerals,
                                               config.maxMinerals);
  std::uniform_int_distribution<int> typeDist(
      0, config.availableMinerals.size() - 1);

  int count = countDist(rng);
  for (int i = 0; i < count; i++) {
    Position pos = randomFreePosition();
    MineralTypes type = config.availableMinerals[typeDist(rng)];

    double freq = 1.0;
    size_t pickaxeHits = PICKAXE_COUNT_COAL;
    switch (type) {
    case MineralTypes::GOLD:
      freq = SPAWN_FREQ_GOLD;
      pickaxeHits = PICKAXE_COUNT_GOLD;
      break;
    case MineralTypes::IRON:
      freq = SPAWN_FREQ_IRON;
      pickaxeHits = PICKAXE_COUNT_IRON;
      break;
    case MineralTypes::LAPIZLAZULI:
      freq = SPAWN_FREQ_LAPIZLAZULI;
      pickaxeHits = PICKAXE_COUNT_LAPIZLAZULI;
      break;
    case MineralTypes::COAL:
      freq = SPAWN_FREQ_COAL;
      pickaxeHits = PICKAXE_COUNT_COAL;
      break;
    }

    addEntity(std::make_unique<Mineral>(pos.x, pos.y, type, freq, pickaxeHits), pos);
  }
}

void CavernSector::spawnEnemies() {
  std::uniform_int_distribution<size_t> groupCountDist(config.minEnemyGroups,
                                                        config.maxEnemyGroups);
  std::uniform_int_distribution<size_t> typeDist(0, config.availableEnemies.size() - 1);

  size_t groupCount = groupCountDist(rng);
  for (size_t i = 0; i < groupCount; i++) {
    const EnemySpawnConfig &spawnCfg = config.availableEnemies[typeDist(rng)];
    std::uniform_int_distribution<size_t> sizeDist(spawnCfg.minGroup, spawnCfg.maxGroup);
    spawnEnemyGroup(spawnCfg.type, sizeDist(rng));
  }
}

void CavernSector::spawnEnemyGroup(EnemyType type, size_t count) {
  Position center = randomFreePosition();

  if (type == EnemyType::VAMPIRE_MALE || type == EnemyType::VAMPIRE_MALE) {
    std::pair<std::unique_ptr<Enemy>, std::unique_ptr<Enemy>> vampires = enemiesFactory.createVampires(center);
    Sector::addEntity(std::move(vampires.first), center);

    Position secondPos = randomNearPosition(center, 2);
    vampires.second->setPosition(secondPos);

    Sector::addEntity(std::move(vampires.second), secondPos);
  } else {
    for (size_t i = 0; i < count; i++) {
      Position pos = (i == 0) ? center : randomNearPosition(center, 2);
      auto enemy = enemiesFactory.createEnemy(type, pos);

      if (enemy) {
        Sector::addEntity(std::move(enemy), pos);
      }
    }
  }
}

Position CavernSector::randomNearPosition(Position center, int radius) {
  std::uniform_int_distribution<int> offsetDist(-radius, radius);
  for (size_t attempts = 0; attempts < 50; attempts++) {
    int nx = std::clamp(static_cast<int>(center.x) + offsetDist(rng), 0, static_cast<int>(width  - 1));
    int ny = std::clamp(static_cast<int>(center.y) + offsetDist(rng), 0, static_cast<int>(height - 1));
      
    Position pos(static_cast<size_t>(nx), static_cast<size_t>(ny));
    if (isEmpty(pos))
      return pos;
  }
  return randomFreePosition();
}

Position CavernSector::randomFreePosition() {
  std::uniform_int_distribution<size_t> xDist(0, width - 1);
  std::uniform_int_distribution<size_t> yDist(0, height - 1);

  for (size_t attempts = 0; attempts < 100; attempts++) {
    Position pos(xDist(rng), yDist(rng));
    if (isEmpty(pos))
      return pos;
  }
  return findFreePosition();
}
