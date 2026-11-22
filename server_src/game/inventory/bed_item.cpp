#include "bed_item.h"

#include "../entities/bed.h"
#include "../sectors/cabin_sector.h"
#include "../sectors/farm_sector.h"

bool BedItem::canBePlacedAt(const Sector &sector, Position) const {
  bool inFarm = dynamic_cast<const FarmSector *>(&sector) != nullptr;
  bool inCabin = dynamic_cast<const CabinSector *>(&sector) != nullptr;
  return inFarm || inCabin;
}

std::unique_ptr<Entity> BedItem::toEntity(Position position) const {
  return std::make_unique<Bed>(position, ownerId);
}