#include "farm_sector.h"

bool FarmSector::hasRoomFor(AnimalType type) const {
  size_t count = 0;
  for (const auto &[position, entity] : this->entities) {
    EntityState state = entity->entityState();
    if (state.type == EntityTypes::ANIMAL && state.animal.type == type)
      count++;
  }
  size_t limit = type == AnimalType::COW ? FARM_MAX_COWS : FARM_MAX_CHICKENS;
  return count < limit;
}



