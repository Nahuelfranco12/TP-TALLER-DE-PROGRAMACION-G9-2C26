#ifndef BED_H_
#define BED_H_

#include "entity.h"
#include "interactable.h"

class Bed : public Entity, public Interactable {
private:
  int ownerId;
  bool occupied = false;

public:
  Bed(Position position, int ownerId)
      : Entity(position.x, position.y, EntityTypes::BED), ownerId(ownerId) {}

  int getOwnerId() const { return ownerId; }
  void release() { occupied = false; }

  void interact(World &world, Player &player) override;

  EntityState entityState() const override {
    EntityState state = Entity::entityState();
    state.bed.sleeping = occupied;
    return state;
  }
};

#endif // BED_H_