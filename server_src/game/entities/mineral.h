#ifndef MINERAL_H_
#define MINERAL_H_

#include <memory>

#include "../game_constants.h"
#include "entity.h"

class Mineral : public Entity {
private:
    MineralTypes mineralType;

    double spawnFrequency;
    MineralPickaxeTime pickaxeTime;

public:
    Mineral(size_t pos_x, size_t pos_y, MineralTypes mineralType, double spawnFrequency, MineralPickaxeTime pickaxeTime) : Entity(pos_x, pos_y, EntityTypes::MINERAL), mineralType(mineralType), spawnFrequency(spawnFrequency), pickaxeTime(pickaxeTime) {}

    MineralTypes getMineralType() const { return mineralType; }
    double getSpawnFrequency() const { return spawnFrequency; }
    MineralPickaxeTime getPickaxeTime() const { return pickaxeTime; }

    std::unique_ptr<Item> toItem() const;
    void pickaxeEffect();
};

#endif // MINERAL_H_