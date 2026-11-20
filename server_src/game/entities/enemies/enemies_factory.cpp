#include "enemies_factory.h"

#include "orc.h"
#include "skeleton.h"
#include "vampire.h"
#include "skull.h"

std::unique_ptr<Enemy> EnemiesFactory::createSkeleton(Position position) {
  EnemyStats stats{SKELETON_LIFE, SKELETON_DAMAGE, SKELETON_DAMAGE, SKELETON_GOLD,
                         SKELETON_TICKS_PER_MOVE, SKELETON_TICKS_PER_ATTACK,
                         SKELETON_SIGHT_RANGE};

  return std::make_unique<Skeleton>(position.x, position.y, stats);
}

std::unique_ptr<Enemy> EnemiesFactory::createOrc(Position position) {
  EnemyStats stats{ORC_LIFE, ORC_DAMAGE, ORC_DAMAGE, ORC_GOLD, ORC_TICKS_PER_MOVE,
                         ORC_TICKS_PER_ATTACK, ORC_SIGHT_RANGE};

  return std::make_unique<Orc>(position.x, position.y, stats);
}

std::unique_ptr<Enemy> EnemiesFactory::createBlueSkull(Position position) {
  EnemyStats stats{SKULL_BLUE_LIFE, SKULL_BLUE_DAMAGE, SKULL_BLUE_DAMAGE,  0, SKULL_BLUE_TICKS_PER_MOVE,
                         SKULL_BLUE_TICKS_PER_ATTACK, SKULL_BLUE_SIGHT_RANGE};

  return std::make_unique<Skull>(position.x, position.y, stats, EnemyType::SKULL_BLUE);
}

std::unique_ptr<Enemy> EnemiesFactory::createGreenSkull(Position position) {
  EnemyStats stats{SKULL_GREEN_LIFE, SKULL_GREEN_DAMAGE, SKULL_GREEN_DAMAGE, 0, SKULL_GREEN_TICKS_PER_MOVE,
                         SKULL_GREEN_TICKS_PER_ATTACK, SKULL_GREEN_SIGHT_RANGE};

  return std::make_unique<Skull>(position.x, position.y, stats, EnemyType::SKULL_GREEN);
}

std::pair<std::unique_ptr<Enemy>, std::unique_ptr<Enemy>>
EnemiesFactory::createVampires(Position firstPos) {
  EnemyStats maleStats{VAMPIRE_LIFE, VAMPIRE_MALE_DAMAGE, VAMPIRE_MALE_DAMAGE, VAMPIRE_GOLD,
                               VAMPIRE_MALE_TICKS_PER_MOVE,
                               VAMPIRE_TICKS_PER_ATTACK, VAMPIRE_SIGHT_RANGE};

  EnemyStats femaleStats{VAMPIRE_LIFE, VAMPIRE_FEMALE_DAMAGE, VAMPIRE_FEMALE_DAMAGE, VAMPIRE_GOLD,
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
  else if (enemyType == EnemyType::SKULL_BLUE)
    return createBlueSkull(position);
  else if (enemyType == EnemyType::SKULL_GREEN)
    return createGreenSkull(position);
  return nullptr;
}

std::unique_ptr<Entity> EnemiesFactory::createTrap(EnemyType trapType,
                                                   Position position,
                                                   DirectionDto direction) {
  if (trapType == EnemyType::TRAP_PINCH)
    return std::make_unique<Trap>(
        position.x, position.y, trapType, direction, TRAP_PINCH_DAMAGE,
        TRAP_ACTIVE_TICKS, TRAP_INACTIVE_TICKS);

  if (trapType == EnemyType::TRAP_FLAME)
    return std::make_unique<Trap>(
        position.x, position.y, trapType, direction, TRAP_FLAME_DAMAGE,
        TRAP_ACTIVE_TICKS, TRAP_INACTIVE_TICKS);

  return nullptr;
}