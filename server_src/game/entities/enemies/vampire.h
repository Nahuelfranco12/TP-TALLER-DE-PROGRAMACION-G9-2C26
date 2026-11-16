#ifndef VAMPIRE_H_
#define VAMPIRE_H_

#include "../../game_constants.h"
#include "enemy.h"

class Vampire : public Enemy {
private:
  EnemyType vampireType;
  Vampire *partner;
  int reviveCountdown;

  bool inFrenzy() const;

public:
  Vampire(size_t pos_x, size_t pos_y, EnemyType kind, EnemyStats vampireStats);

  void setPartner(Vampire *otherVampire);

  bool removeOnDeath() const override;
  int getDamage() const override;
  int getTicksPerMove() const override;

  void tick() override;
  Decision decide(const Sector &sector) override;
};

#endif