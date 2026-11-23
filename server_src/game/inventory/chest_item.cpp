#include "chest_item.h"

#include "../entities/chest.h"
#include "../sectors/cabin_sector.h"
#include "../sectors/farm_sector.h"

bool ChestItem::canBePlacedAt(const Sector &sector, Position) const {
  bool inFarm = dynamic_cast<const FarmSector *>(&sector) != nullptr;
  bool inCabin = dynamic_cast<const CabinSector *>(&sector) != nullptr;
  return inFarm || inCabin;
}

std::unique_ptr<Entity> ChestItem::toEntity(Position position) const {
  return std::make_unique<Chest>(position);
}