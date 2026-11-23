#ifndef ENEMIES_FACTORY_H_
#define ENEMIES_FACTORY_H_

#include <memory>

#include "../../game_constants.h"
#include "../../position.h"
#include "enemy.h"
#include "trap.h"

class EnemiesFactory {
private:
  std::unique_ptr<Enemy> createSkeleton(Position position);
  std::unique_ptr<Enemy> createOrc(Position position);
  std::unique_ptr<Enemy> createBlueSkull(Position position);
  std::unique_ptr<Enemy> createGreenSkull(Position position);

public:
  std::pair<std::unique_ptr<Enemy>, std::unique_ptr<Enemy>>
  createVampires(Position firstPos);
  std::unique_ptr<Enemy> createEnemy(EnemyType enemyType, Position position);
  std::unique_ptr<Entity> createTrap(EnemyType trapType, Position position,
                                     DirectionDto direction = DirectionDto::Up);
};

#endif // ENEMIES_FACTORY_H_
