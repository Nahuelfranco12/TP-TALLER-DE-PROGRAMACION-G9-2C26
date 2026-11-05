#ifndef COW_H_
#define COW_H_

#include "animal.h"

#define TICKS_FOR_MILK 1000

class Cow : public Animal {
private:
  int progress = 0;
public:
  Cow(size_t pos_x, size_t pos_y) : Animal(pos_x, pos_y, AnimalType::COW, TICKS_FOR_MILK) {}
};

#endif // COW_H_
