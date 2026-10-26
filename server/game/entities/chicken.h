#ifndef CHICKEN_H_
#define CHICKEN_H_

#include "animal.h"

class Chicken : public Animal {
public:
    Chicken(size_t pos_x, size_t pos_y) : Animal(pos_x, pos_y, AnimalType::CHICKEN) {}
};

#endif // CHICKEN_H_
