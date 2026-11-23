#ifndef CHEST_H_
#define CHEST_H_

#include "../inventory/inventory.h"
#include "entity.h"
#include "interactable.h"

class Chest : public Entity, public Interactable {
private:
  Inventory inventory;
  int openedBy = INVALID_PLAYER_ID;

public:
  explicit Chest(Position position)
      : Entity(position.x, position.y, EntityTypes::FURNITURE) {}

  Inventory &getInventory() { return inventory; }
  bool isOpenedBy(int playerId) const { return openedBy == playerId; }
  void closeFor(int playerId) {
    if (openedBy == playerId)
      openedBy = INVALID_PLAYER_ID;
  }

  void interact(World &world, Player &player) override;

  EntityState entityState() const override {
    EntityState state = Entity::entityState();
    state.furniture.type = FurnitureType::CHEST;
    state.chest.inventory = inventory.state();
    state.chest.openedBy = openedBy;
    return state;
  }
};

#endif // CHEST_H_