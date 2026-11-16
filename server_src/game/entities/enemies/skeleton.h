#ifndef SKELETON_H_
#define SKELETON_H_

#include "enemy.h"

class Skeleton : public Enemy {
private:
  int ticksDead;

public:
  Skeleton(size_t pos_x, size_t pos_y, EnemyStats skeletonStats)
      : Enemy(EnemyType::SKELETON, pos_x, pos_y, skeletonStats),
        ticksDead(0) {}

  bool removeOnDeath() const override { return false; }

  void tick() override {
    Enemy::tick();
    if (!isDead())
      return;
    ticksDead++;
    if (ticksDead >= SKELETON_REVIVE_TICKS) {
      restoreHits(SKELETON_LIFE);
      ticksDead = 0;
    }
  }

};

#endif // SKELETON_H_