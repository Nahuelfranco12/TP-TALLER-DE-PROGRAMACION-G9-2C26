#include "player.h"
#include "mineral.h"
#include "../sector.h"

MoveResult Player::move(Position destination) {
    return this->actualSector->move(this->position, destination);
    // TODO: si MoveResult.idSector != actualSector->getId() actualizar actualSector (puertas)
}

void Player::mine(Mineral& mineral) {
    if (!this->position.isAdjacentTo(mineral.position))
        return;
    Tool* pickaxe = this->inventory.getTool(AvailableTools::PICKAXE);
    if (!pickaxe) return;

    auto item = mineral.toItem();
    auto removed = this->actualSector->removeEntity(mineral.position);
    if (!removed) return;

    this->inventory.addItem(std::move(item));
}
