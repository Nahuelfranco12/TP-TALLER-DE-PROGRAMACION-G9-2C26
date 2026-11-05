#ifndef ENTITY_H_
#define ENTITY_H_

#include "../../world_state.h"
#include "../position.h"

class Entity {
private:
  EntityTypes entityType;

public:
  Position position;

  Entity(size_t pos_x, size_t pos_y, EntityTypes type)
      : entityType(type), position(pos_x, pos_y) {}
  virtual ~Entity() = default;

  void setPosition(Position newPosition) { this->position = newPosition; }
  virtual EntityTypes getType() const { return this->entityType; }

  virtual EntityState entityState() const {
    return EntityState{entityType, position, INVALID_PLAYER_ID, MineralTypes{}, AnimalType{}, false};
  }
  
  virtual void tick() {}
};

#endif // ENTITY_H_
