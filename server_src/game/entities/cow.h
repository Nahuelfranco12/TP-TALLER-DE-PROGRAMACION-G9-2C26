#ifndef COW_H_
#define COW_H_

#include "animal.h"
#include "collectable.h"
#include "../inventory/cow_milk.h"
#include "../game_constants.h"

class Cow : public Animal, public ICollectable {
private:
  int progress = 0;
  int ticksToBeReady;

public:
  Cow(size_t pos_x, size_t pos_y) : Animal(pos_x, pos_y, AnimalType::COW), ticksToBeReady(TICKS_FOR_MILK) {}

  void tick() override {
    if (progress < ticksToBeReady)
      progress += 1;
  }

  bool canCollect() const override {
    if (progress == ticksToBeReady)
      return true;
    return false;
  }

  std::unique_ptr<Item> collect() override {
    if (canCollect()) {
      progress = 0;
      return std::make_unique<CowMilk>(PRICE_MILK);
    }
    return nullptr;
  }
};

#endif // COW_H_
