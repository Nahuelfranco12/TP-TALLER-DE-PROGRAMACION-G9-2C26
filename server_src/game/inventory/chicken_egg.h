#ifndef CHICKEN_EGG_H_
#define CHICKEN_EGG_H_

#include "item.h"

class ChickenEgg : public Item {
public:
  explicit ChickenEgg(double price)
      : Item(price, ItemType::ANIMAL_PRODUCT, AnimalType::CHICKEN) {}

  bool stacksWith(const Item &other) const override;
};

#endif // CHICKEN_EGG_H_
