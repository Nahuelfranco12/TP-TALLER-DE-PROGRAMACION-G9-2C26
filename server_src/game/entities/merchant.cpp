#include "merchant.h"

#include "../../../common_src/constants.h"
#include "../world.h"

Merchant::Merchant(Position position, MerchantType merchantType, const std::string &name, const std::string &greeting):
    Entity(position.x, position.y, EntityTypes::NPC), merchantType(merchantType), name(name), greeting(greeting) {}


const Offer *Merchant::find(const std::vector<Offer> &offers,
                            const std::string &productName) const {
  for (const Offer &offer : offers)
    if (offer.name == productName)
      return &offer;
  return nullptr;
}

void Merchant::addSale(const std::string &productName, int price, std::unique_ptr<Item> sample) {
    sales.push_back({productName, price, std::move(sample)});
}

void Merchant::addPurchase(const std::string &productName, int price, std::unique_ptr<Item> sample) {
    purchases.push_back({productName, price, std::move(sample)});
}

const Offer *Merchant::findSale(const std::string &productName) const {
    return find(sales, productName);
}

const Offer *Merchant::findPurchase(const std::string &productName) const {
    return find(purchases, productName);
}

const std::string &Merchant::getName() const {
    return name;
}

const std::vector<Offer> &Merchant::getSales() const {
    return sales;
}

const std::vector<Offer> &Merchant::getPurchases() const {
    return purchases;
}


void Merchant::interact(World &world, Player &player) {
    player.startTalkingTo(*this);
    world.addChat({SYSTEM_SENDER_ID, name, player.getId(), greeting + 
                                " Comandos: /consultar_catalogo, "
                                "/comprar <producto> <cantidad>, "
                                "/vender <producto> <cantidad>"});
}

EntityState Merchant::entityState() const {
    EntityState state = Entity::entityState();
    state.merchant.type = merchantType;
    return state;
}