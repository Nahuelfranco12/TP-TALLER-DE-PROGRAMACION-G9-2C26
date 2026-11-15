#include "cavern_sector.h"

#include "../entities/mineral.h"
#include "../entities/skeleton.h"

#include <memory>
#include <random>
#include <utility>

bool CavernSector::addEntity(std::unique_ptr<Entity> entity, Position pos) {
  if (entity->getType() == EntityTypes::PLAYER && playerCount() == 0)
    reset();
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
  std::uniform_int_distribution<size_t> countDist(config.minEnemies,
                                                  config.maxEnemies);

  std::uniform_int_distribution<size_t> typeDist(
      0, static_cast<size_t>(EnemyType::COUNT) - 1);
  int count = countDist(rng);
  for (int i = 0; i < count; i++) { 
    EnemyType randType = static_cast<EnemyType>(typeDist(rng)); 
    Position pos = randomFreePosition();
    addEntity(this->enemiesFactory.createEnemy(randType, pos), pos);
  }
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
