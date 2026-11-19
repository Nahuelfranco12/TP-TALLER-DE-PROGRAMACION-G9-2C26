#ifndef MERCHANT_H_
#define MERCHANT_H_

#include "entity.h"

class Merchant : public Entity {
private:
    MerchantType merchantType;

public:
    Merchant(Position position, MerchantType MerchantType);

    EntityState entityState() const override;
};

#endif // MERCHANT_H_