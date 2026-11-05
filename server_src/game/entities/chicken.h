#ifndef CHICKEN_H_
#define CHICKEN_H_

#include "animal.h"

#define TICKS_FOR_EGG 100

class Chicken : public Animal {
private:
  int progress = 0;
public:
  Chicken(size_t pos_x, size_t pos_y)
      : Animal(pos_x, pos_y, AnimalType::CHICKEN, TICKS_FOR_EGG) {}
};

#endif // CHICKEN_H_
