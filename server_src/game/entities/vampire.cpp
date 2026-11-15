#include "vampire.h"

#include "../sectors/sector.h"

Vampire::Vampire(size_t pos_x, size_t pos_y, EnemyType vampireType):
    Enemy(pos_x, pos_y, vampireType == EnemyType::VAMPIRE_FEMALE
        ? EnemyStats{VAMPIRE_LIFE, VAMPIRE_FEMALE_DAMAGE, VAMPIRE_GOLD, VAMPIRE_FEMALE_TICKS_PER_MOVE, VAMPIRE_TICKS_PER_ATTACK, VAMPIRE_SIGHT_RANGE}
        : EnemyStats{VAMPIRE_LIFE, VAMPIRE_MALE_DAMAGE, VAMPIRE_GOLD, VAMPIRE_MALE_TICKS_PER_MOVE, VAMPIRE_TICKS_PER_ATTACK, VAMPIRE_SIGHT_RANGE}),
      vampireType(vampireType), partner(nullptr), reviveCountdown(-1) {}

void Vampire::setPartner(Vampire *otherVampire) {
    partner = otherVampire;
}

bool Vampire::inFrenzy() const {
    return !isDead() && partner != nullptr && partner->isDead();
}

bool Vampire::removeOnDeath() const {
    return false;
}

int Vampire::getDamage() const {
    if (vampireType == EnemyType::VAMPIRE_MALE && inFrenzy())
        return stats.damage * 2;
    return stats.damage;
}

int Vampire::getTicksPerMove() const {
    if (vampireType == EnemyType::VAMPIRE_FEMALE && inFrenzy())
        return stats.ticksPerMove / 2;
    return stats.ticksPerMove;
}

void Vampire::tick() {
    Enemy::tick();
    if (reviveCountdown > 0) {
        reviveCountdown--;
        if (reviveCountdown == 0) {
        restoreHits(VAMPIRE_LIFE);
        reviveCountdown = -1;
        }
    }
}

Decision Vampire::decide(const Sector &sector) {
    if(isDead()) {
        if(reviveCountdown < 0 && sector.bloodNear(position, VAMPIRE_BLOOD_RANGE))
            reviveCountdown = VAMPIRE_REVIVE_TICKS;
        return Decision{};
    }
    return Enemy::decide(sector);
}

EntityState Vampire::entityState() const {
    EntityState state = Entity::entityState();
    state.enemy.type = vampireType;
    state.enemy.is_alive = !isDead();
    return state;
}