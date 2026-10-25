#ifndef MINERAL_H_
#define MINERAL_H_

#include "entity.h"

class Mineral : public Entity {
private:
    double spawnFrequency;
    double pickaxeTime;

public:
    void pickaxeEffect();
};

#endif // MINERAL_H_
