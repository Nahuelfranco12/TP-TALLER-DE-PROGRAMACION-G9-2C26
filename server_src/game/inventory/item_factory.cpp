#include "item_factory.h"

#include "chicken_egg.h"
#include "cow_milk.h"
#include "crop_item.h"
#include "seed.h"
#include "mineral_item.h"
#include "animal_item.h"
#include "chest_item.h"
#include "decoration_item.h"

std::unique_ptr<Item> ItemFactory::create(ItemType type, int subtype, int price, CropQuality quality) const {
  switch (type) {
  case ItemType::SEED:
    return std::make_unique<Seed>(price, static_cast<CropTypes>(subtype));
  case ItemType::CROP:
    return std::make_unique<CropItem>(price, static_cast<CropTypes>(subtype), quality);
  case ItemType::MINERAL:
    return std::make_unique<MineralItem>(price, static_cast<MineralTypes>(subtype));
  case ItemType::ANIMAL_PRODUCT:
    if (static_cast<AnimalType>(subtype) == AnimalType::COW)
      return std::make_unique<CowMilk>(price);
    return std::make_unique<ChickenEgg>(price);
  case ItemType::ANIMAL:
    return std::make_unique<AnimalItem>(price, static_cast<AnimalType>(subtype));
  case ItemType::FURNITURE:
    FurnitureType furniture = static_cast<FurnitureType>(subtype);
    if (furniture == FurnitureType::CHEST)
      return std::make_unique<ChestItem>(price);
    if (furniture == FurnitureType::BED)
      return nullptr;
    return std::make_unique<DecorationItem>(price, furniture);
  }
  return nullptr;
}