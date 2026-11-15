#include "enemies_factory.h"

#include "skeleton.h"
#include "orc.h"

std::unique_ptr<Enemy> EnemiesFactory::createSkeleton(Position position) {
    return std::make_unique<Skeleton>(position.x, position.y);
}

std::unique_ptr<Enemy> EnemiesFactory::createOrc(Position position) {
    return std::make_unique<Orc>(position.x, position.y);
}

std::unique_ptr<Enemy> EnemiesFactory::createEnemy(EnemyType enemyType, Position position) {
    switch (enemyType)
    {
    case EnemyType::SKELETON:
        return createSkeleton(position);

    case EnemyType::ORC:
        return createOrc(position);
    
    default:
        break;
    }
    return nullptr;
}