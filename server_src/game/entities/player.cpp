#include "player.h"

#include <iostream>
#include <utility>

#include "../sectors/sector.h"
#include "enemies/enemy.h"
#include "mineral.h"
#include "../inventory/item_factory.h"
#include "server_src/game/game_constants.h"

MoveResult Player::move(Position destination) {
  if (isUnconscious() || sleeping)
    return MoveResult(false, this->position, this->actualSector->getId());
  this->actualSector->closeChestsOf(this->id);
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
bool Player::mine(Mineral &mineral) {
  if (isUnconscious())
    return false;
  if (!this->position.isAdjacentTo(mineral.position))
    return false;
  // cppcheck-suppress constVariablePointer
  if (this->actualTool == nullptr ||
      this->actualTool->toolType != AvailableTools::PICKAXE)
    return false;

  // TODO: Falta el chequeo de efecto secundario de algunos minerales

  if (mineral.hit()) {
    this->spendEnergy(ENERGY_COST_MINE);
    auto item = mineral.toItem();
    auto removed = this->actualSector->removeEntity(mineral.position);
    if (!removed)
      return false;

    this->inventory.addItem(std::move(item));
    return true;
  }
  return false;
}

bool Player::attack(Enemy &enemy) {
  if (isUnconscious())
    return false;
  if (!this->position.isAdjacentTo(enemy.position))
    return false;
  if (this->actualTool == nullptr ||
      this->actualTool->toolType != AvailableTools::SWORD)
    return false;
  if (enemy.isDead())
    return false;

  size_t damage = SWORD_DAMAGE;
  if (isBadlyHurt())
    damage /= 2;

  if (enemy.hit(damage)) {
    this->spendEnergy(ENERGY_COST_ATTACK);
    this->coins += enemy.getGoldDrop();
    bool killed = enemy.isDead();
    if (killed && enemy.removeOnDeath()) {
      this->actualSector->removeEntity(enemy.position);
    }
    return killed;
  }
  return false;
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

void Player::setLife(double value) {
  life = value < 0 ? 0 : (value > PLAYER_MAX_LIFE ? PLAYER_MAX_LIFE : value);
}

void Player::setEnergy(double value) {
  energy = value < 0
               ? 0
               : (value > PLAYER_MAX_ENERGY ? PLAYER_MAX_ENERGY : value);
}

void Player::restoreEnergy(size_t amount) {
  setEnergy(energy + amount);
}

void Player::takeDamage(double amount) {
  life -= amount;
  if (life < 0)
    life = 0;

  if (actualSector && actualSector->getId() >= IdSector::CAVERN_LEVEL_1 &&
      actualSector->getId() <= IdSector::CAVERN_LEVEL_10) {
    tookDamageInCavernFlag = true;
  }
}

void Player::startNewDay(bool sleptInBed) {
  double factor = sleptInBed ? 1.0 : 0.5;
  this->life = PLAYER_MAX_LIFE * factor;
  this->energy = PLAYER_MAX_ENERGY * factor;
  this->sleeping = false;
}

int Player::buy(const Item &sample, int price, int amount) {
  ItemFactory factory;
  int bought = 0;
  while (bought < amount && coins >= price && inventory.addItem(factory.create(sample.getType(),
                                          sample.subtypeToInt(), price))) {
    coins -= price;
    bought++;
  }
  return bought;
}

bool Player::sell(const Item &sample, int price, int amount, int &earned) {
  double multipliers = 0;
  if (!inventory.remove(sample, amount, multipliers))
    return false;
  earned = static_cast<int>(price * multipliers);
  coins += earned;
  return true;
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
