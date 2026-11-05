#include "player.h"

#include <utility>

#include "../sector.h"
#include "mineral.h"

MoveResult Player::move(Position destination) {
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
  if (!this->position.isAdjacentTo(mineral.position))
    return;
  // cppcheck-suppress constVariablePointer
  if (this->actualTool == nullptr ||
      this->actualTool->toolType != AvailableTools::PICKAXE)
    return;

  // TODO: Falta el chequeo de efecto secundario de algunos minerales

  auto item = mineral.toItem();
  auto removed = this->actualSector->removeEntity(mineral.position);
  if (!removed)
    return;

  this->inventory.addItem(std::move(item));
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
                     this->inventory.state()};
}
