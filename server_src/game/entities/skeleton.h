#ifndef SKELETON_H_
#define SKELETON_H_

#include "enemy.h"


class Skeleton : public Enemy {
private:
    int ticksDead;
public:
    Skeleton(size_t pos_x, size_t pos_y) :
        Enemy(pos_x, pos_y, EnemyStats{SKELETON_HITS, SKELETON_GOLD}), ticksDead(0) {}
    
    bool removeOnDeath() const override {
        return false;
    }
    
    void tick() override {
        if(!isDead())
            return;
        ticksDead++;
        if(ticksDead >= SKELETON_REVIVE_TICKS) {
            restoreHits(SKELETON_HITS);
            ticksDead = 0;
        }
    }

    EntityState entityState() const override {
        EntityState state = Entity::entityState();
        state.enemy.type = EnemyType::SKELETON;
        state.enemy.is_alive = !isDead();
        return state;
    }
};

#endif // SKELETON_H_