#ifndef SEED_H_
#define SEED_H_

#include "item.h"

class Seed : public Item {
private:
public:
    Seed(double price) : Item(price) {};
};

#endif // SEED_H_