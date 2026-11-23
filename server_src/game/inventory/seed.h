#ifndef SEED_H_
#define SEED_H_

#include "item.h"

class Seed : public Item {
public:
  explicit Seed(double price, CropTypes type)
      : Item(price, ItemType::SEED, type) {}
};

#endif // SEED_H_
