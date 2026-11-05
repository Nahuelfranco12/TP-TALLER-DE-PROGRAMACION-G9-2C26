#include "crop_item.h"

CropItem::CropItem(double price, CropTypes cropType, CropQuality quality): Item(price, ItemType::CROP, cropType) {}

CropQuality CropItem::getQuality() const {
    return quality;
}

bool CropItem::stacksWith(const Item &other) const {
    if (this->getType() != other.getType())
        return false;

    const CropItem *o = dynamic_cast<const CropItem *>(&other);

    if (!o)
        return false;
    return this->getSubtype() == o->getSubtype() && this->quality == o->quality;
}