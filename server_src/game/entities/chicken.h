#ifndef CHICKEN_H_
#define CHICKEN_H_

#include "../game_constants.h"
#include "../inventory/chicken_egg.h"
#include "animal.h"
#include "collectable.h"

#include <memory>

class Chicken : public Animal, public ICollectable {
private:
  int progress = 0;
  int ticksToBeReady;

public:
  Chicken(size_t pos_x, size_t pos_y)
      : Animal(pos_x, pos_y, AnimalType::CHICKEN),
        ticksToBeReady(TICKS_FOR_EGG) {}

  void tick() override {
    if (progress < ticksToBeReady)
      progress += 1;
  }

  bool canCollect() const override {
    if (progress >= ticksToBeReady)
      return true;
    return false;
  }

  std::unique_ptr<Item> collect() override {
    if (canCollect()) {
      progress = 0;
      return std::make_unique<ChickenEgg>(PRICE_EGG);
    }
    return nullptr;
  }

  EntityState entityState() const override {
    EntityState state = Animal::entityState();
    state.animal.is_ready = canCollect();
    return state;
  }

  bool removeOnCollect() const override { return false; }
};

#endif // CHICKEN_H_
