#ifndef ENEMIES_FACTORY_H_
#define ENEMIES_FACTORY_H_

#include <memory>

#include "../game_constants.h"
#include "../position.h"
#include "enemy.h"


class EnemiesFactory {
private:
    std::unique_ptr<Enemy> createSkeleton(Position position);
    std::unique_ptr<Enemy> createOrc(Position position); 

public:
    std::unique_ptr<Enemy> createEnemy(EnemyType enemyType, Position position);
};

#endif // ENEMIES_FACTORY_H_
