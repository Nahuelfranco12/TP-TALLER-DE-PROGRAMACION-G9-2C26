#include "enemies_factory.h"

#include "orc.h"
#include "skeleton.h"
#include "vampire.h"

std::unique_ptr<Enemy> EnemiesFactory::createSkeleton(Position position) {
  return std::make_unique<Skeleton>(position.x, position.y);
}

std::unique_ptr<Enemy> EnemiesFactory::createOrc(Position position) {
  return std::make_unique<Orc>(position.x, position.y);
}

std::pair<std::unique_ptr<Enemy>, std::unique_ptr<Enemy>>
EnemiesFactory::createVampires(Position firstPos) {
  std::unique_ptr<Vampire> maleVamp = std::make_unique<Vampire>(
      firstPos.x, firstPos.y, EnemyType::VAMPIRE_MALE);
  std::unique_ptr<Vampire> femaleVamp = std::make_unique<Vampire>(
      firstPos.x, firstPos.y, EnemyType::VAMPIRE_FEMALE);

  maleVamp->setPartner(femaleVamp.get());
  femaleVamp->setPartner(maleVamp.get());

  return {std::move(maleVamp), std::move(femaleVamp)};
}

std::unique_ptr<Enemy> EnemiesFactory::createEnemy(EnemyType enemyType,
                                                   Position position) {
  switch (enemyType) {
  case EnemyType::SKELETON:
    return createSkeleton(position);

  case EnemyType::ORC:
    return createOrc(position);

  case EnemyType::VAMPIRE_MALE:
    break;

  case EnemyType::VAMPIRE_FEMALE:
    break;

  default:
    break;
  }
  return nullptr;
}