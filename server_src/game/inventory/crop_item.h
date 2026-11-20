#ifndef CROP_ITEM_H_
#define CROP_ITEM_H_

#include "item.h"

class CropItem : public Item {
private:
  CropQuality quality;

public:
  CropItem(double price, CropTypes cropType, CropQuality quality);
  CropQuality getQuality() const;
  bool stacksWith(const Item &other) const override;

  std::unique_ptr<Item> clone() const override {
    return std::make_unique<CropItem>(*this);
  }
};

#endif // CROP_ITEM_H_
