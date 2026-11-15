#ifndef ENEMY_H_
#define ENEMY_H_

#include <cstddef>

#include "../game_constants.h"
#include "entity.h"
#include "hittable.h"
#include "../decision.h"

class Sector;

struct EnemyStats {
    size_t maxLife;
    int damage;
    int gold;
    int ticksPerMove;
    int ticksPerAttack;
    int sightRange;
};

class Enemy : public Entity, public Hittable {
protected:
    EnemyStats stats;
    int moveCooldown;
    int attackCooldown;

public:
    Enemy(size_t pos_x, size_t pos_y, const EnemyStats &stats);

    int getGoldDrop() const;
    virtual int getDamage() const;
    virtual int getTicksPerMove() const;

    bool isDead() const;

    // TODO : revisar si esto es importante (lo puse para esqueletos sobretodo)
    virtual bool removeOnDeath() const;

    void tick() override;

    virtual Decision decide(const Sector& sector);
};

#endif // ENEMY_H_