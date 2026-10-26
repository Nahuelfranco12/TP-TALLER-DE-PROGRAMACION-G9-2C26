#ifndef SEED_H_
#define SEED_H_

#include "item.h"

class Seed : public Item {
public:
    explicit Seed(double price) : Item(price, ItemType::SEED) {}
};

#endif // SEED_H_
