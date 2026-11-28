#include "village_sector.h"
#include "../entities/merchant.h"

void VillageSector::endDay() {
  for (auto &[position, entity] : entities) {
    Merchant *merchant = dynamic_cast<Merchant *>(entity.get());
    if (merchant)
      merchant->refreshCatalog();
  }
}