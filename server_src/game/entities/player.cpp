#include "player.h"

#include <utility>

#include "../sector.h"
#include "mineral.h"

MoveResult Player::move(Position destination) {
  return this->actualSector->move(this->position, destination);
  // TODO: si MoveResult.idSector != actualSector->getId() actualizar
  // actualSector (puertas)
}

void Player::selectTool(AvailableTools tool) {
  this->actualTool = *this->inventory.getTool(tool);
}

Tool& Player::getSelectedTool() {
  return this->actualTool;
}

// cppcheck-suppress constParameterReference
void Player::mine(Mineral &mineral) {
  if (!this->position.isAdjacentTo(mineral.position))
    return;
  // cppcheck-suppress constVariablePointer
  Tool *pickaxe = this->inventory.getTool(AvailableTools::PICKAXE);
  if (!pickaxe)
    return;

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
                     this->inventory.state()};
}
