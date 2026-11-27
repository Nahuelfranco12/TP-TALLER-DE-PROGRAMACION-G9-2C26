#ifndef ROTATING_MERCHANT_H_
#define ROTATING_MERCHANT_H_

#include <cstdlib>
#include <string>
#include <utility>
#include <vector>

#include "merchant.h"

class RotatingMerchant : public Merchant {
private:
    size_t dailyProducts;
    std::vector<Offer> stock;

public:
    RotatingMerchant(Position position, MerchantType merchantType,
                     const std::string &name, const std::string &greeting,
                     size_t dailyProducts)
        : Merchant(position, merchantType, name, greeting),
          dailyProducts(dailyProducts) {}

    void refreshCatalog() override;
};

#endif // ROTATING_MERCHANT_H_