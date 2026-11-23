#ifndef SKULL_H_
#define SKULL_H_

#include "enemy.h"

class Skull : public Enemy {
private:
public:
  Skull(size_t pos_x, size_t pos_y, EnemyStats skullStats, EnemyType skullType)
      : Enemy(skullType, pos_x, pos_y, skullStats) {}

  bool removeOnDeath() const override { return false; }

  size_t getAttackRange() const override {
    return stats.sightRange;
  }

  void tick() override {
    Enemy::tick();
    if (!isDead())
        restoreHits(this->stats.maxLife);
  }

};

#endif // SKULL_H_
