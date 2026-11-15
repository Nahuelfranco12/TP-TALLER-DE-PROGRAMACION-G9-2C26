#ifndef ENEMY_H_
#define ENEMY_H_

#include <cstddef>

#include "../game_constants.h"
#include "entity.h"
#include "hittable.h"

struct EnemyStats {
    size_t hitsToKill;
    int gold;
};

class Enemy : public Entity, public Hittable {
    protected:
    EnemyStats stats;

    public:
    Enemy(size_t pos_x, size_t pos_y, const EnemyStats &stats): 
        Entity(pos_x, pos_y, EntityTypes::ENEMY), Hittable(stats.hitsToKill), stats(stats) {}

    int getGoldDrop() const {
        return stats.gold; 
    }

    bool isDead() const {
        return getHitsLeft() == 0;
    }

    // TODO : revisar si esto es importante (lo puse para esqueletos sobretodo)
    virtual bool removeOnDeath() const {
        return true;
    }
};

#endif // ENEMY_H_