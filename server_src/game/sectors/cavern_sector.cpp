#include "cavern_sector.h"
#include "../entities/enemies/orc.h"

#include "../entities/mineral.h"
#include "../entities/enemies/skeleton.h"

#include <algorithm>
#include <memory>
#include <random>
#include <utility>

bool CavernSector::tryAddEntity(std::unique_ptr<Entity> &entity, Position pos) {
  if (entity->getType() == EntityTypes::PLAYER && playerCount() == 0)
    reset();

  if (entity->getType() == EntityTypes::PLAYER && !isEmpty(pos)) {
    Position freePosition(0, 0);
    if (!findFreePosition(freePosition))
      return false;
    pos = freePosition;
  }

  return Sector::tryAddEntity(entity, pos);
}

void CavernSector::initEntities() {
  spawnMinerals();
  spawnEnemies();
  spawnTraps();
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

  traps.clear();
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
    int breakChance = 0;
    int hordeChance = 0;
    switch (type) {
    case MineralTypes::GOLD:
      freq = SPAWN_FREQ_GOLD;
      pickaxeHits = PICKAXE_COUNT_GOLD;
      break;
    case MineralTypes::IRON:
      freq = SPAWN_FREQ_IRON;
      pickaxeHits = PICKAXE_COUNT_IRON;
      hordeChance = IRON_HORDE_CHANCE;
      break;
    case MineralTypes::LAPIZLAZULI:
      freq = SPAWN_FREQ_LAPIZLAZULI;
      pickaxeHits = PICKAXE_COUNT_LAPIZLAZULI;
      breakChance = LAPIZLAZULI_BREAK_CHANCE;
      break;
    case MineralTypes::COAL:
      freq = SPAWN_FREQ_COAL;
      pickaxeHits = PICKAXE_COUNT_COAL;
      break;
    }

    std::unique_ptr<Entity> mineral =
        std::make_unique<Mineral>(pos.x, pos.y, type, freq, pickaxeHits, breakChance, hordeChance);
    tryAddEntity(mineral, pos);
  }
}

void CavernSector::spawnEnemies() {
  std::uniform_int_distribution<size_t> groupCountDist(config.minEnemyGroups, config.maxEnemyGroups);
  std::uniform_int_distribution<size_t> typeDist(0, config.availableEnemies.size() - 1);

  for (EnemySpawnConfig &spawnCfg : config.availableEnemies)
    spawnCfg.currentCount = 0;
  bool skullSpawned = false;
  size_t groupCount = groupCountDist(rng);

  for (size_t i = 0; i < groupCount; i++) {
    EnemySpawnConfig *selected = nullptr;
    size_t attempts = 0;

    while (attempts < config.availableEnemies.size() && selected == nullptr) {
      EnemySpawnConfig &candidate = config.availableEnemies[typeDist(rng)];

      bool isSkull = candidate.type == EnemyType::SKULL_BLUE || candidate.type == EnemyType::SKULL_GREEN;
      size_t remaining = candidate.maxLevel - candidate.currentCount;

      bool canSpawn = remaining >= candidate.minGroup && (!isSkull || !skullSpawned);
      if (canSpawn)
        selected = &candidate;
      attempts++;
    }

    if (selected != nullptr) {
      size_t remaining = selected->maxLevel - selected->currentCount;
      size_t maxGroup = std::min(selected->maxGroup, remaining);

      std::uniform_int_distribution<size_t> sizeDist(selected->minGroup, maxGroup);
      size_t count = sizeDist(rng);

      spawnEnemyGroup(selected->type, count, randomFreePosition());
      selected->currentCount += count;

      bool isSkull = selected->type == EnemyType::SKULL_BLUE ||
                     selected->type == EnemyType::SKULL_GREEN;

      if (isSkull)
        skullSpawned = true;
    }
  }
}

void CavernSector::spawnTraps() {
  for (size_t i = 0; i < TRAP_PINCH_COUNT; i++) {
    Position pos = randomFreePosition();
    std::unique_ptr<Entity> trap =
        enemiesFactory.createTrap(EnemyType::TRAP_PINCH, pos);
    if (trap)
      Sector::tryAddEntity(trap, pos);
  }

  std::uniform_int_distribution<size_t> sideDist(0, 1);
  std::uniform_int_distribution<size_t> yDist(0, height - 1);

  size_t spawned = 0;
  for (size_t attempts = 0;
       spawned < TRAP_FLAME_COUNT && attempts < TRAP_FLAME_COUNT * 20;
       attempts++) {
    bool leftWall = sideDist(rng) == 0;
    Position pos(leftWall ? 0 : width - 1, yDist(rng));
    DirectionDto direction =
        leftWall ? DirectionDto::Right : DirectionDto::Left;

    if (!isEmpty(pos) || this->doors.find(pos) != this->doors.end())
      continue;

    std::unique_ptr<Entity> trap =
        enemiesFactory.createTrap(EnemyType::TRAP_FLAME, pos, direction);
    if (trap && Sector::tryAddEntity(trap, pos))
      spawned++;
  }
}

void CavernSector::spawnEnemyGroup(EnemyType type, size_t count, Position center) {
  if (type == EnemyType::VAMPIRE_MALE || type == EnemyType::VAMPIRE_FEMALE) {
    std::pair<std::unique_ptr<Enemy>, std::unique_ptr<Enemy>> vampires =
        enemiesFactory.createVampires(center);
    std::unique_ptr<Entity> first = std::move(vampires.first);
    bool resultVampire = Sector::tryAddEntity(first, center);
    if (!resultVampire)
      return;

    Position secondPos = randomNearPosition(center, 2);
    vampires.second->setPosition(secondPos);

    std::unique_ptr<Entity> second = std::move(vampires.second);
    resultVampire = Sector::tryAddEntity(second, secondPos);
    if (!resultVampire)
      Sector::removeEntity(center);
  } else {
    int groupId = (type == EnemyType::ORC) ? nextOrcGroupId++ : -1;
    for (size_t i = 0; i < count; i++) {
      Position pos = (i == 0) ? center : randomNearPosition(center, 2);
      auto enemy = enemiesFactory.createEnemy(type, pos);

      if (enemy) {
        if (type == EnemyType::ORC) {
          Orc *orc = dynamic_cast<Orc *>(enemy.get());
          if (orc)
            orc->setGroupId(groupId);
        }
        std::unique_ptr<Entity> entity = std::move(enemy);
        Sector::tryAddEntity(entity, pos);
      }
    }
  }
}

Position CavernSector::randomNearPosition(Position center, int radius) {
  std::uniform_int_distribution<int> offsetDist(-radius, radius);
  for (size_t attempts = 0; attempts < 50; attempts++) {
    int nx = std::clamp(static_cast<int>(center.x) + offsetDist(rng), 0,
                        static_cast<int>(width - 1));
    int ny = std::clamp(static_cast<int>(center.y) + offsetDist(rng), 0,
                        static_cast<int>(height - 1));

    Position pos(static_cast<size_t>(nx), static_cast<size_t>(ny));
    if (isEmpty(pos) && this->traps.find(pos) == this->traps.end() &&
      this->doors.find(pos) == this->doors.end())
      return pos;
  }
  return randomFreePosition();
}

Position CavernSector::randomFreePosition() {
  std::uniform_int_distribution<size_t> xDist(0, width - 1);
  std::uniform_int_distribution<size_t> yDist(0, height - 1);

  for (size_t attempts = 0; attempts < 100; attempts++) {
    Position pos(xDist(rng), yDist(rng));
    if (isEmpty(pos) && this->traps.find(pos) == this->traps.end() &&
      this->doors.find(pos) == this->doors.end())
      return pos;
  }
  return findFreePosition();
}

void CavernSector::spawnHordeNear(Position playerPosition) {
  std::uniform_int_distribution<size_t> sizeDist(ORC_MIN_GROUP, ORC_MAX_GROUP);
  Position center = randomNearPosition(playerPosition, ORC_HORDE_RADIUS);
  spawnEnemyGroup(EnemyType::ORC, sizeDist(rng), center);
}
