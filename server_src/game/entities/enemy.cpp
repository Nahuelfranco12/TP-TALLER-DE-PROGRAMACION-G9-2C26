#include "enemy.h"
#include <cstdlib>
#include <iostream>
#include "../sectors/sector.h"

Enemy::Enemy(size_t pos_x, size_t pos_y, const EnemyStats &stats): 
        Entity(pos_x, pos_y, EntityTypes::ENEMY), Hittable(stats.maxLife), stats(stats), moveCooldown(0), attackCooldown(0) {}

int Enemy::getGoldDrop() const {
    return stats.gold; 
}

int Enemy::getDamage() const {
    return stats.damage;
}

int Enemy::getTicksPerMove() const {
    return stats.ticksPerMove;
}

bool Enemy::isDead() const {
    return getHitsLeft() == 0;
}

bool Enemy::removeOnDeath() const {
    return true;
}

void Enemy::tick() {
    if (moveCooldown > 0)
        moveCooldown--;
    if (attackCooldown > 0)
        attackCooldown--;
}

Decision Enemy::decide(const Sector& sector) {
    if(isDead())
        return Decision{};

    Position target(0, 0);
    if(!sector.closestPlayer(position, stats.sightRange, target))
        return Decision{};
    
    int dx = static_cast<int>(target.x) - static_cast<int>(position.x);
    int dy = static_cast<int>(target.y) - static_cast<int>(position.y);

    DirectionDto direction = DirectionDto::Up;
    if(std::abs(dx) >= std::abs(dy)) {
        if(dx > 0) {
            direction = DirectionDto::Right;
        } else {
            direction = DirectionDto::Left;
        }
    } else {
        if(dy > 0) {
            direction = DirectionDto::Down;
        } else {
            direction = DirectionDto::Up;
        }
    }

    if(std::abs(dx) + std::abs(dy) == 1) {
        if(attackCooldown > 0)
            return Decision{};
        attackCooldown = stats.ticksPerAttack;
        return Decision{DecisionType::ATTACK, direction};
    }

    if (moveCooldown > 0) 
        return Decision{};
    moveCooldown = getTicksPerMove();
    return Decision{DecisionType::MOVE, direction};
}