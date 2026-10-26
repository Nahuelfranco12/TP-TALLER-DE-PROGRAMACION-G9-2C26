#ifndef ANIMAL_H_
#define ANIMAL_H_

#include "entity.h"

enum class AnimalType { COW, CHICKEN };

class Animal : public Entity {
private:
    AnimalType animalType;

public:
    Animal(size_t pos_x, size_t pos_y, AnimalType animalType) : Entity(pos_x, pos_y), animalType(animalType) {}

    virtual ~Animal() = default;

    AnimalType getAnimalType() const { return animalType; }
};

#endif // ANIMAL_H_
