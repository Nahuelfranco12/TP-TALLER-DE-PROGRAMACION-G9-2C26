#ifndef DECORATION_H_
#define DECORATION_H_

#include "../game_constants.h"
#include "entity.h"

class Decoration : public Entity {
private:
  FurnitureType decorationType;

public:
  Decoration(Position position, FurnitureType decorationType)
      : Entity(position.x, position.y, EntityTypes::FURNITURE),
        decorationType(decorationType) {}

  EntityState entityState() const override {
    EntityState state = Entity::entityState();
    state.furniture.type = decorationType;
    return state;
  }
};

#endif // DECORATION_H_