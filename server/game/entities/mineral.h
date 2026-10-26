#ifndef MINERAL_H_
#define MINERAL_H_

#include "entity.h"

enum MineralTypes { GOLD, IRON, LAPIZLAZULI, COAL };
enum MineralPickaxeTime { LOW, MEDIUM, HIGH, VERY_HIGH };

class Mineral : public Entity {
private:
    MineralTypes type;

    double spawnFrequency;
    MineralPickaxeTime pickaxeTime;

public:
    Mineral(size_t pos_x, size_t pos_y, MineralTypes type, double spawnFrequency, MineralPickaxeTime pickaxeTime) : Entity(pos_x, pos_y), type(type), spawnFrequency(spawnFrequency), pickaxeTime(pickaxeTime) {};

    void pickaxeEffect();
};

#endif // MINERAL_H_
