#ifndef COW_H_
#define COW_H_

#include "animal.h"

class Cow : public Animal {
public:
  Cow(size_t pos_x, size_t pos_y) : Animal(pos_x, pos_y, AnimalType::COW) {}
};

#endif // COW_H_
