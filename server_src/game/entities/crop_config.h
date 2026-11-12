#ifndef CROP_CONFIG_H_
#define CROP_CONFIG_H_

#include <cstddef>

#include "../game_constants.h"

struct CropConfig {
  size_t wateringsPerDay;
  size_t daysToGrow;
  size_t maxSkippedWaterings;
  size_t extraHarvests;
};

inline const CropConfig &cropConfig(CropTypes type) {
  static const CropConfig strawberry{2, 1, 0, 2};
  static const CropConfig greenOnion{3, 2, 0, 0};
  static const CropConfig potato{2, 2, 1, 0};
  static const CropConfig pumpkin{1, 7, 0, 0};

  switch (type) {
    case CropTypes::STRAWBERRY:
        return strawberry;
    case CropTypes::GREEN_ONION:
        return greenOnion;
    case CropTypes::POTATO:
        return potato;
    case CropTypes::PUMPKIN:
        return pumpkin;
  }
  return pumpkin;
}

#endif // CROP_CONFIG_H_
