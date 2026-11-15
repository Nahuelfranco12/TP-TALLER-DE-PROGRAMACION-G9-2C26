#ifndef ORC_H_
#define ORC_H_

#include "enemy.h"

class Orc : public Enemy {
private:
public:
  Orc(size_t pos_x, size_t pos_y)
      : Enemy(pos_x, pos_y,
              EnemyStats{ORC_LIFE, ORC_DAMAGE, ORC_GOLD, ORC_TICKS_PER_MOVE,
                         ORC_TICKS_PER_ATTACK, ORC_SIGHT_RANGE}) {}

  bool removeOnDeath() const override { return true; }

  void tick() override {
    Enemy::tick();
    if (!isDead())
      return;
  }

  EntityState entityState() const override {
    EntityState state = Entity::entityState();
    state.enemy.type = EnemyType::ORC;
    state.enemy.is_alive = !isDead();
    return state;
  }
};

#endif // ORC_H_
