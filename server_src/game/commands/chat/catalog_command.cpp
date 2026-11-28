#include "catalog_command.h"

#include "../../entities/merchant.h"
#include "../../game_constants.h"

void CatalogCommand::trade(World &world, Player &, const Merchant &merchant) {
  if (merchant.getSales().empty() && merchant.getPurchases().empty()) {
    reply(world, merchant, "Por ahora no tengo nada para ofrecerte.");
    return;
  }
  if (!merchant.getSales().empty()) {
    std::string sales = "Vendo:";
    for (const Offer &offer : merchant.getSales()) {
      int price = offer.price;
      if (world.isMarketDiscountActive())
        price = offer.price * (100 - SET_MONEY_RECOMPENSE_DISCOUNT) / 100;
      sales += " " + offer.name + " $" + std::to_string(price);
    }
    reply(world, merchant, sales);
  }
  if (!merchant.getPurchases().empty()) {
    std::string purchases = "Compro:";
    for (const Offer &offer : merchant.getPurchases()) {
      int price = offer.price;
      if (world.isMoneySetRewardActive())
        price = offer.price * SET_MONEY_RECOMPENSE_PRICE_INCREASE;
      purchases += " " + offer.name + " $" + std::to_string(price);
    }
    reply(world, merchant, purchases);
  }
}