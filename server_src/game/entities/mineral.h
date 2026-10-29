#ifndef MINERAL_H_
#define MINERAL_H_

#include <memory>

#include "../game_constants.h"
#include "entity.h"

class Mineral : public Entity {
private:
    MineralTypes type;

    double spawnFrequency;
    MineralPickaxeTime pickaxeTime;

public:
    Mineral(size_t pos_x, size_t pos_y, MineralTypes type, double spawnFrequency, MineralPickaxeTime pickaxeTime) : Entity(pos_x, pos_y), type(type), spawnFrequency(spawnFrequency), pickaxeTime(pickaxeTime) {}

    MineralTypes getMineralType() const { return type; }
    double getSpawnFrequency() const { return spawnFrequency; }
    MineralPickaxeTime getPickaxeTime() const { return pickaxeTime; }

    std::unique_ptr<Item> toItem() const;
    void pickaxeEffect();
};

#endif // MINERAL_H_