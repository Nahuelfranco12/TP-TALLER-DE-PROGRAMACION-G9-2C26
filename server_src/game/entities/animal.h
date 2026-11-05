#ifndef ANIMAL_H_
#define ANIMAL_H_

#include "../game_constants.h"
#include "entity.h"

class Animal : public Entity {
private:
  AnimalType animalType;
  int progress = 0;
  int ticksToBeReady;

public:
  Animal(size_t pos_x, size_t pos_y, AnimalType animalType, int ticksToBeReady)
      : Entity(pos_x, pos_y, EntityTypes::ANIMAL), animalType(animalType), ticksToBeReady(ticksToBeReady) {}

  ~Animal() override = default;

  AnimalType getAnimalType() const { return animalType; }

  EntityState entityState() const override {
    EntityState state = Entity::entityState();
    state.animalType = animalType;
    state.is_ready = isReady();
    return state;
  }

  void tick() override {
        if (progress < ticksToBeReady)
            progress += 1;
    }

  bool isReady() const { return progress >= ticksToBeReady; }
};

#endif // ANIMAL_H_
