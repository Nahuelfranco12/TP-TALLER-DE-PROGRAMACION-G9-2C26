#ifndef MINERAL_H_
#define MINERAL_H_

#include "entity.h"

class Mineral : public Entity {
private:
    double spawnFrequency;
    double pickaxeTime;

public:
    Mineral(size_t pos_x, size_t pos_y, double spawnFrequency, double pickaxeTime) : Entity(pos_x, pos_y), spawnFrequency(spawnFrequency), pickaxeTime(pickaxeTime) {};

    void pickaxeEffect();
};

#endif // MINERAL_H_
