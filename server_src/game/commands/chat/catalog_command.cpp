#include "catalog_command.h"

#include "../../entities/merchant.h"

void CatalogCommand::trade(World &world, Player &, const Merchant &merchant) {
  if (merchant.getSales().empty() && merchant.getPurchases().empty()) {
    reply(world, merchant, "Por ahora no tengo nada para ofrecerte.");
    return;
  }
  if (!merchant.getSales().empty()) {
    std::string sales = "Vendo:";
    for (const Offer &offer : merchant.getSales())
      sales += " " + offer.name + " $" + std::to_string(offer.price);
    reply(world, merchant, sales);
  }
  if (!merchant.getPurchases().empty()) {
    std::string purchases = "Compro:";
    for (const Offer &offer : merchant.getPurchases())
      purchases += " " + offer.name + " $" + std::to_string(offer.price);
    reply(world, merchant, purchases);
  }
}