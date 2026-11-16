#ifndef TRAP_H_
#define TRAP_H_

#include <cstddef>

#include "../../game_constants.h"
#include "../entity.h"

class Trap : public Entity {
private:
  EnemyType trapType;
  DirectionDto direction;
  int damage;
  size_t activeTicks;
  size_t inactiveTicks;
  size_t remainingTicks;
  bool active;

public:
  Trap(size_t pos_x, size_t pos_y, EnemyType trapType,
       DirectionDto direction, int damage, size_t activeTicks,
       size_t inactiveTicks)
      : Entity(pos_x, pos_y, EntityTypes::ENEMY), trapType(trapType),
        direction(direction), damage(damage), activeTicks(activeTicks),
        inactiveTicks(inactiveTicks), remainingTicks(inactiveTicks),
        active(false) {}

  void tick() override {
    if (remainingTicks > 0)
      remainingTicks--;

    if (remainingTicks == 0) {
      active = !active;
      remainingTicks = active ? activeTicks : inactiveTicks;
    }
  }

  bool isActive() const { return active; }
  EnemyType getTrapType() const { return trapType; }
  DirectionDto getDirection() const { return direction; }
  int getDamage() const { return damage; }

  EntityState entityState() const override {
    EntityState state = Entity::entityState();
    state.enemy.type = trapType;
    state.enemy.direction = direction;
    return state;
  }
};

#endif // TRAP_H_
