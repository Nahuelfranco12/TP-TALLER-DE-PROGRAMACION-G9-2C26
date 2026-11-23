#ifndef ANIMAL_ITEM_H_
#define ANIMAL_ITEM_H_

#include "item.h"
#include "placeable.h"

class AnimalItem : public Item, public Placeable {
private:
    AnimalType animalType;
public:
  AnimalItem(double price, AnimalType animalType)
      : Item(price, ItemType::ANIMAL, animalType), animalType(animalType) {}

  bool canBePlacedAt(const Sector &sector, Position position) const override;

  std::unique_ptr<Entity> toEntity(Position position) const override;
};

#endif // ANIMAL_ITEM_H_