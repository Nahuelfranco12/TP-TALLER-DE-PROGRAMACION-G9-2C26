#include "player.h"

#include <iostream>
#include <utility>

#include "../sectors/sector.h"
#include "enemies/enemy.h"
#include "mineral.h"

MoveResult Player::move(Position destination) {
  if (isUnconscious())
    return MoveResult(false, this->position, this->actualSector->getId());
  return this->actualSector->move(this->position, destination);
}

void Player::selectTool(AvailableTools tool) {
  Tool *found = this->inventory.getTool(tool);
  if (found != nullptr) {
    this->actualTool = found;
  }
}

Tool *Player::getSelectedTool() { return this->actualTool; }

// cppcheck-suppress constParameterReference
void Player::mine(Mineral &mineral) {
  if (isUnconscious())
    return;
  if (!this->position.isAdjacentTo(mineral.position))
    return;
  // cppcheck-suppress constVariablePointer
  if (this->actualTool == nullptr ||
      this->actualTool->toolType != AvailableTools::PICKAXE)
    return;

  // TODO: Falta el chequeo de efecto secundario de algunos minerales

  if (mineral.hit()) {
    auto item = mineral.toItem();
    auto removed = this->actualSector->removeEntity(mineral.position);
    if (!removed)
      return;

    this->inventory.addItem(std::move(item));
  }
}

void Player::attack(Enemy &enemy) {
  if (isUnconscious())
    return;
  if (!this->position.isAdjacentTo(enemy.position))
    return;
  if (this->actualTool == nullptr ||
      this->actualTool->toolType != AvailableTools::SWORD)
    return;
  if (enemy.isDead())
    return;

  size_t damage = SWORD_DAMAGE;
  if (isBadlyHurt())
    damage /= 2;

  if (enemy.hit(damage)) {
    this->coins += enemy.getGoldDrop();
    if (enemy.removeOnDeath()) {
      this->actualSector->removeEntity(enemy.position);
    }
  }
}

bool Player::hasEnergy(size_t cost) {
  if (this->energy <= 0 || this->energy < cost)
    return false;
  return true;
}

bool Player::isBadlyHurt() const {
  return life <= PLAYER_MAX_LIFE * PLAYER_LOW_LIFE_PERCENT / 100;
}

bool Player::spendEnergy(size_t cost) {
  if (!this->hasEnergy(cost))
    return false;
  this->energy -= cost;
  return true;
}

void Player::restoreEnergy(size_t amount) {
  if ((this->energy + amount) >= PLAYER_MAX_ENERGY)
    this->energy = PLAYER_MAX_ENERGY;
  this->energy += amount;
}

void Player::takeDamage(double amount) {
  life -= amount;
  if (life < 0)
    life = 0;
}

PlayerState Player::state() const {
  return PlayerState{this->id,
                     this->position,
                     this->life,
                     this->energy,
                     this->coins,
                     this->actualSector->getId(),
                     PlayerOutfitState{this->outfit.hat, this->outfit.hair,
                                       this->outfit.tshirt, this->outfit.pants},
                     this->actualTool != nullptr ? this->actualTool->toolType
                                                 : AvailableTools{},
                     this->inventory.state(),
                     this->pendingGift.giverId,
                     this->pendingGift.item};
}
