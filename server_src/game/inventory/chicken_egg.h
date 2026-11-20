#ifndef CHICKEN_EGG_H_
#define CHICKEN_EGG_H_

#include "item.h"

class ChickenEgg : public Item {
public:
  explicit ChickenEgg(double price)
      : Item(price, ItemType::ANIMAL_PRODUCT, AnimalType::CHICKEN) {}

  bool stacksWith(const Item &other) const override;

  std::unique_ptr<Item> clone() const override {
    return std::make_unique<ChickenEgg>(*this);
  }
};

#endif // CHICKEN_EGG_H_
