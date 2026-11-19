#include "merchant.h"

Merchant::Merchant(Position position, MerchantType MerchantType):
    Entity(position.x, position.y, EntityTypes::NPC), merchantType(merchantType) {}

EntityState Merchant::entityState() const {
    EntityState state = Entity::entityState();
    state.merchant.type = merchantType;
    return state;
}