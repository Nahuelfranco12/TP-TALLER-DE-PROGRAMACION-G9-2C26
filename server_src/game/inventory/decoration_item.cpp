#include "decoration_item.h"

#include "../entities/decoration.h"
#include "../sectors/cabin_sector.h"
#include "../sectors/farm_sector.h"

bool DecorationItem::canBePlacedAt(const Sector &sector, Position) const {
  bool isFarm = dynamic_cast<const FarmSector *>(&sector) != nullptr;
  bool isCabin = dynamic_cast<const CabinSector *>(&sector) != nullptr;
  return isFarm || isCabin;
}

std::unique_ptr<Entity> DecorationItem::toEntity(Position position) const {
  return std::make_unique<Decoration>(position, decorationType);
}