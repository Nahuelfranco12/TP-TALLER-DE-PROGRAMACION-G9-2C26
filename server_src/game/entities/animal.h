#ifndef ANIMAL_H_
#define ANIMAL_H_

#include "../game_constants.h"
#include "entity.h"

class Animal : public Entity {
private:
  AnimalType animalType;

public:
  Animal(size_t pos_x, size_t pos_y, AnimalType animalType)
      : Entity(pos_x, pos_y, EntityTypes::ANIMAL), animalType(animalType) {}

  ~Animal() override = default;

  AnimalType getAnimalType() const { return animalType; }

  EntityState entityState() const override {
    EntityState state = Entity::entityState();
    state.animalType = animalType;
    return state;
  }
};

#endif // ANIMAL_H_
