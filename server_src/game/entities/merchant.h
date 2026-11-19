#ifndef MERCHANT_H_
#define MERCHANT_H_

#include "interactable.h"
#include "entity.h"

class Merchant : public Entity, public Interactable {
private:
    MerchantType merchantType;
    std::string name;
    std::string greeting;

public:
    Merchant(Position position, MerchantType MerchantType, const std::string &name, const std::string &greeting);

    EntityState entityState() const override;

    void interact(World &world, Player &player) override;
};

#endif // MERCHANT_H_