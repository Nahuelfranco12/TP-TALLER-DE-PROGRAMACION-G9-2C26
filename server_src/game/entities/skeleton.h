#ifndef SKELETON_H_
#define SKELETON_H_

#include "enemy.h"


class Skeleton : public Enemy {
private:
    int ticksDead;
public:
    Skeleton(size_t pos_x, size_t pos_y) :
        Enemy(pos_x, pos_y, EnemyStats{SKELETON_LIFE, SKELETON_DAMAGE, SKELETON_GOLD, SKELETON_TICKS_PER_MOVE, SKELETON_TICKS_PER_ATTACK, SKELETON_SIGHT_RANGE}), ticksDead(0) {}
    
    bool removeOnDeath() const override {
        return false;
    }
    
    void tick() override {
        Enemy::tick();
        if(!isDead())
            return;
        ticksDead++;
        if(ticksDead >= SKELETON_REVIVE_TICKS) {
            restoreHits(SKELETON_LIFE);
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