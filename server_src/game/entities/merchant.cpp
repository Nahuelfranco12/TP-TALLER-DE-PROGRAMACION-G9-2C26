#include "merchant.h"

#include "../../../common_src/constants.h"
#include "../world.h"

Merchant::Merchant(Position position, MerchantType MerchantType, const std::string &name, const std::string &greeting):
    Entity(position.x, position.y, EntityTypes::NPC), merchantType(merchantType), name(name), greeting(greeting) {}

EntityState Merchant::entityState() const {
    EntityState state = Entity::entityState();
    state.merchant.type = merchantType;
    return state;
}

void Merchant::interact(World &world, Player &player) {
  world.addChat({SYSTEM_SENDER_ID, name, player.getId(), greeting + 
                            " Comandos: /consultar_catalogo, "
                            "/comprar <producto> <cantidad>, "
                            "/vender <producto> <cantidad>"});
}