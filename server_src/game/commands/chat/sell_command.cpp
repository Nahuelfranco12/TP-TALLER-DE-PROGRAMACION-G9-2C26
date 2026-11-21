#include "sell_command.h"

#include "../../entities/merchant.h"
#include "../../entities/player.h"

void SellCommand::trade(World &world, Player &player, const Merchant &merchant) {
  std::string productName;
  int amount = 0;
  if (!readProductAndAmount(args, productName, amount)) {
    reply(world, merchant, "Se escribe asi: /vender <producto> <cantidad>");
    return;
  }

  const Offer *offer = merchant.findPurchase(productName);
  if (!offer) {
    reply(world, merchant, "No compro " + productName + ". Mira /consultar_catalogo");
    return;
  }

  if (!player.sell(*offer->sample, offer->price, amount)) {
    reply(world, merchant, "No tenes " + std::to_string(amount) + " " + productName);
    return;
  }

  reply(world, merchant, "Te pague $" + std::to_string(offer->price * amount));
}