#ifndef MERCHANTS_FACTORY_H_
#define MERCHANTS_FACTORY_H_

#include <memory>

#include "merchant.h"

class MerchantsFactory {
public:
  std::unique_ptr<Merchant> create(MerchantType type, Position position) const;
};

#endif // MERCHANTS_FACTORY_H_