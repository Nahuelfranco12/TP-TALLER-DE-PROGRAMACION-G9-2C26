#include "cavern_sector.h"

#include "../entities/mineral.h"

#include <random>

bool CavernSector::addEntity(std::unique_ptr<Entity> entity, Position pos) {
    if (entity->getType() == EntityTypes::PLAYER && playerCount() == 0)
        reset();
    return Sector::addEntity(std::move(entity), pos);
}

void CavernSector::reset() {
    clearEntities();
    spawnMinerals();
    // spawnEnemies();
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
    std::uniform_int_distribution<int> countDist(config.minMinerals, config.maxMinerals);
    std::uniform_int_distribution<int> typeDist(0, config.availableMinerals.size() - 1);

    int count = countDist(rng);
    for (int i = 0; i < count; i++) {
        Position pos = randomFreePosition();
        MineralTypes type = config.availableMinerals[typeDist(rng)];

        double freq = 1.0;
        MineralPickaxeTime time = MineralPickaxeTime::MEDIUM;
        switch (type) {
            case MineralTypes::GOLD:
                freq = SPAWN_FREQ_GOLD;
                time = MineralPickaxeTime::HIGH;
                break;
            case MineralTypes::IRON:
                freq = SPAWN_FREQ_IRON;
                time = MineralPickaxeTime::MEDIUM;
                break;
            case MineralTypes::LAPIZLAZULI:
                freq = SPAWN_FREQ_LAPIZLAZULI;
                time = MineralPickaxeTime::MEDIUM;
                break;
            case MineralTypes::COAL:
                freq = SPAWN_FREQ_COAL;
                time = MineralPickaxeTime::LOW;
                break;
        }
        addEntity(std::make_unique<Mineral>(pos.x, pos.y, type, freq, time), pos);
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