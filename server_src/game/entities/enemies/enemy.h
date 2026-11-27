#ifndef ENEMY_H_
#define ENEMY_H_

#include <cstddef>

#include "../../decision.h"
#include "../../game_constants.h"
#include "../entity.h"
#include "../hittable.h"

class Sector;

struct EnemyStats {
  size_t maxLife;
  int damage;
  int defaultDamage;
  int gold;
  int ticksPerMove;
  int ticksPerAttack;
  int sightRange;
};

class Enemy : public Entity, public Hittable {
protected:
  EnemyType type;
  EnemyStats stats;
  int moveCooldown;
  int attackCooldown;
  bool cheated = false;

public:
  Enemy(EnemyType type, size_t pos_x, size_t pos_y, const EnemyStats &stats);

  int getGoldDrop() const;
  EnemyType getEnemyType() const { return type; }
  virtual int getDamage() const;
  virtual int getTicksPerMove() const;
  virtual size_t getAttackRange() const;

  void cheat() {
    cheated = !cheated;
    if (cheated)
      this->stats.damage = 0;
    else
      this->stats.damage = this->stats.defaultDamage;
  }

  bool isDead() const;

  // TODO : revisar si esto es importante (lo puse para esqueletos sobretodo)
  virtual bool removeOnDeath() const;

  void tick() override;

  virtual Decision decide(const Sector &sector);
  virtual void apply(Sector &sector, Position origin,
                     const Decision &decision);

  EntityState entityState() const override {
    EntityState state = Entity::entityState();
    state.enemy.type = this->type;
    state.enemy.is_alive = !isDead();
    return state;
  }
};

#endif // ENEMY_H_