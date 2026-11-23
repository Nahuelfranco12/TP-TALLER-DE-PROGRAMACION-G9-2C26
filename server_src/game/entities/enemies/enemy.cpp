#include "enemy.h"

#include "../../sectors/sector.h"
#include "../player.h"
#include <cstdlib>
#include <iostream>

Enemy::Enemy(EnemyType type, size_t pos_x, size_t pos_y, const EnemyStats &stats)
    : type(type), Entity(pos_x, pos_y, EntityTypes::ENEMY), Hittable(stats.maxLife),
      stats(stats), moveCooldown(0), attackCooldown(0) {}

int Enemy::getGoldDrop() const { return stats.gold; }

int Enemy::getDamage() const { return stats.damage; }

int Enemy::getTicksPerMove() const { return stats.ticksPerMove; }

size_t Enemy::getAttackRange() const { return 1; }


bool Enemy::isDead() const { return getHitsLeft() == 0; }

bool Enemy::removeOnDeath() const { return true; }

void Enemy::tick() {
  if (moveCooldown > 0)
    moveCooldown--;
  if (attackCooldown > 0)
    attackCooldown--;
}

Decision Enemy::decide(const Sector &sector) {
  if (isDead())
    return Decision{};

  Position target(0, 0);
  if (!sector.closestPlayer(position, stats.sightRange, target))
    return Decision{};

  int dx = static_cast<int>(target.x) - static_cast<int>(position.x);
  int dy = static_cast<int>(target.y) - static_cast<int>(position.y);

  DirectionDto direction = DirectionDto::Up;
  if (std::abs(dx) >= std::abs(dy)) {
    if (dx > 0) {
      direction = DirectionDto::Right;
    } else {
      direction = DirectionDto::Left;
    }
  } else {
    if (dy > 0) {
      direction = DirectionDto::Down;
    } else {
      direction = DirectionDto::Up;
    }
  }

  int distance = std::abs(dx) + std::abs(dy);

  if (distance <= static_cast<int>(getAttackRange())) {
    if (attackCooldown > 0)
      return Decision{};

    attackCooldown = stats.ticksPerAttack;

    Decision attack{DecisionType::ATTACK, direction};
    attack.target = target;
    return attack;
  }

  if (moveCooldown > 0)
    return Decision{};
  moveCooldown = getTicksPerMove();
  return Decision{DecisionType::MOVE, direction};
}

void Enemy::apply(Sector &sector, Position origin,
                  const Decision &decision) {
  if (isDead())
    return;

  switch (decision.type) {
  case DecisionType::MOVE: {
    Position target = origin.next(decision.direction);
    sector.move(origin, target);
    break;
  }

  case DecisionType::ATTACK: {
    Position target = origin;

    if (decision.target.has_value()) {
      target = decision.target.value();
    } else {
      int x = static_cast<int>(origin.x);
      int y = static_cast<int>(origin.y);

      switch (decision.direction) {
      case DirectionDto::Up:
        y--;
        break;
      case DirectionDto::Down:
        y++;
        break;
      case DirectionDto::Left:
        x--;
        break;
      case DirectionDto::Right:
        x++;
        break;
      }

      if (x < 0 || y < 0 || x >= static_cast<int>(sector.getWidth()) ||
          y >= static_cast<int>(sector.getHeight()))
        return;

      target = Position(static_cast<size_t>(x), static_cast<size_t>(y));
    }

    int dx = static_cast<int>(target.x) - static_cast<int>(origin.x);
    int dy = static_cast<int>(target.y) - static_cast<int>(origin.y);
    int distance = std::abs(dx) + std::abs(dy);

    if (distance > static_cast<int>(getAttackRange()))
      return;

    Player *player = dynamic_cast<Player *>(sector.getEntity(target));
    if (player && !player->isUnconscious())
      player->takeDamage(getDamage());
    break;
  }

  case DecisionType::NONE:
    break;
  }
}
