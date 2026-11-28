#include "buy_command.h"

#include "../../entities/merchant.h"
#include "../../entities/player.h"
#include "../../game_constants.h"

void BuyCommand::trade(World &world, Player &player, const Merchant &merchant) {
  std::string productName;
  int amount = 0;
  if (!readProductAndAmount(args, productName, amount)) {
    reply(world, merchant, "Se escribe asi: /comprar <producto> <cantidad>");
    return;
  }

  const Offer *offer = merchant.findSale(productName);
  if (!offer) {
    reply(world, merchant, "No vendo " + productName + ". Mira /consultar_catalogo");
    return;
  }

  int unitPrice = offer->price;
  if (world.isMarketDiscountActive())
    unitPrice = offer->price * (100 - SET_MONEY_RECOMPENSE_DISCOUNT) / 100;

  int cost = unitPrice * amount;
  if (static_cast<int>(player.getCoins()) < cost) {
    reply(world, merchant, "No te alcanza: cuesta $" + std::to_string(cost));
    return;
  }

  int bought = player.buy(*offer->sample, unitPrice, amount);
  if (bought == 0) {
    reply(world, merchant, "No tenes lugar en el inventario");
    return;
  }

  std::string message = "Te vendi " + std::to_string(bought) + " " + productName + " por $" + std::to_string(unitPrice * bought);
  if (bought < amount)
    message += " (no entraban mas)";
  reply(world, merchant, message);
}