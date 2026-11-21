#include "crop_item.h"

CropItem::CropItem(double price, CropTypes cropType, CropQuality quality)
    : Item(price, ItemType::CROP, cropType), quality(quality) {}

CropQuality CropItem::getQuality() const { return quality; }

bool CropItem::stacksWith(const Item &other) const {
  if (this->getType() != other.getType())
    return false;

  const CropItem *o = dynamic_cast<const CropItem *>(&other);

  if (!o)
    return false;
  return this->getSubtype() == o->getSubtype() && this->quality == o->quality;
}

double CropItem::priceMultiplier() const {
  switch (quality) {
  case CropQuality::BASE:
    return CROP_MULTIPLIER_BASE;
  case CropQuality::GOOD:
    return CROP_MULTIPLIER_GOOD;
  case CropQuality::EXCELENT:
    return CROP_MULITPLIER_EXCELENT;
  case CropQuality::INCREDIBLE:
    return CROP_MULTIPLIER_INCREDIBLE;
  case CropQuality::PERFECT:
    return CROP_MULTIPLIER_PERFECT;
  }
  return CROP_MULTIPLIER_BASE;
}