#ifndef COW_MILK_H_
#define COW_MILK_H_

#include "item.h"

class CowMilk : public Item {
public:
  explicit CowMilk(double price)
      : Item(price, ItemType::ANIMAL_PRODUCT, AnimalType::COW) {}

  bool stacksWith(const Item &other) const override;
};

#endif // COW_MILK_H_
