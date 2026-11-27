#include "vampire.h"

#include "../../sectors/sector.h"

Vampire::Vampire(size_t pos_x, size_t pos_y, EnemyType kind, EnemyStats vampireStats)
    : Enemy(kind, pos_x, pos_y, vampireStats), partner(nullptr), reviveCountdown(-1) {}

void Vampire::setPartner(Vampire *otherVampire) { partner = otherVampire; }

bool Vampire::inFrenzy() const {
  return !isDead() && partner != nullptr && partner->isDead();
}

bool Vampire::removeOnDeath() const { return false; }

int Vampire::getDamage() const {
  if (type == EnemyType::VAMPIRE_MALE && inFrenzy())
    return stats.damage * 2;
  return stats.damage;
}

int Vampire::getTicksPerMove() const {
  if (type == EnemyType::VAMPIRE_FEMALE && inFrenzy())
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
  if (isDead()) {
    if (reviveCountdown < 0 && sector.bloodNear(position, VAMPIRE_BLOOD_RANGE))
      reviveCountdown = VAMPIRE_REVIVE_TICKS;
    return Decision{};
  }
  return Enemy::decide(sector);
}
