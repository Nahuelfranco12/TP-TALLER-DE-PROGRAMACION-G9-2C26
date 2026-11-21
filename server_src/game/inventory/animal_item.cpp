#include "animal_item.h"

#include "../entities/chicken.h"
#include "../entities/cow.h"
#include "../sectors/farm_sector.h"

bool AnimalItem::canBePlacedAt(const Sector &sector, Position) const {
  const FarmSector *farm = dynamic_cast<const FarmSector *>(&sector);
  if (!farm)
    return false;

  return farm->hasRoomFor(animalType);
}

std::unique_ptr<Entity> AnimalItem::toEntity(Position position) const {
  if (animalType == AnimalType::COW)
    return std::make_unique<Cow>(position.x, position.y);
  return std::make_unique<Chicken>(position.x, position.y);
}