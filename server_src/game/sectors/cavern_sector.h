#ifndef CAVERN_SECTOR_H_
#define CAVERN_SECTOR_H_

#include "sector.h"

struct CavernLevelConfig {
    int minMinerals;
    int maxMinerals;
    int minEnemies;
    int maxEnemies;
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
    Position randomFreePosition();

public:
    CavernSector(size_t width, size_t height, IdSector id, CavernLevelConfig config) : Sector(width, height, id, Terrain(true, false, TerrainType::GROUND)), config(config) {
        reset();
    }

    void reset() override;
    void endDay() override;
};

#endif // CAVERN_SECTOR_H_
