#include "enemies_factory.h"

#include "orc.h"
#include "skeleton.h"
#include "vampire.h"

std::unique_ptr<Enemy> EnemiesFactory::createSkeleton(Position position) {
  EnemyStats stats{SKELETON_LIFE, SKELETON_DAMAGE, SKELETON_GOLD,
                         SKELETON_TICKS_PER_MOVE, SKELETON_TICKS_PER_ATTACK,
                         SKELETON_SIGHT_RANGE};

  return std::make_unique<Skeleton>(position.x, position.y, stats);
}

std::unique_ptr<Enemy> EnemiesFactory::createOrc(Position position) {
  EnemyStats stats{ORC_LIFE, ORC_DAMAGE, ORC_GOLD, ORC_TICKS_PER_MOVE,
                         ORC_TICKS_PER_ATTACK, ORC_SIGHT_RANGE};

  return std::make_unique<Orc>(position.x, position.y, stats);
}

std::pair<std::unique_ptr<Enemy>, std::unique_ptr<Enemy>>
EnemiesFactory::createVampires(Position firstPos) {
  EnemyStats maleStats{VAMPIRE_LIFE, VAMPIRE_MALE_DAMAGE, VAMPIRE_GOLD,
                               VAMPIRE_MALE_TICKS_PER_MOVE,
                               VAMPIRE_TICKS_PER_ATTACK, VAMPIRE_SIGHT_RANGE};

  EnemyStats femaleStats{VAMPIRE_LIFE, VAMPIRE_FEMALE_DAMAGE, VAMPIRE_GOLD,
                             VAMPIRE_FEMALE_TICKS_PER_MOVE,
                             VAMPIRE_TICKS_PER_ATTACK, VAMPIRE_SIGHT_RANGE};

  std::unique_ptr<Vampire> maleVamp = std::make_unique<Vampire>(firstPos.x, firstPos.y, EnemyType::VAMPIRE_MALE, maleStats);
  std::unique_ptr<Vampire> femaleVamp = std::make_unique<Vampire>(
      firstPos.x, firstPos.y, EnemyType::VAMPIRE_FEMALE, femaleStats);

  maleVamp->setPartner(femaleVamp.get());
  femaleVamp->setPartner(maleVamp.get());

  return {std::move(maleVamp), std::move(femaleVamp)};
}

std::unique_ptr<Enemy> EnemiesFactory::createEnemy(EnemyType enemyType,
                                                   Position position) {

  if (enemyType == EnemyType::SKELETON)
    return createSkeleton(position);
  else if (enemyType == EnemyType::ORC)
    return createOrc(position);
  return nullptr;
}