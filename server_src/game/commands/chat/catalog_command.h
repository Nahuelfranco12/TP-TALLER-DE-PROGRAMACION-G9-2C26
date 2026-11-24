#ifndef CATALOG_COMMAND_H_
#define CATALOG_COMMAND_H_

#include "merchant_command.h"

class CatalogCommand : public MerchantCommand {
protected:
  void trade(World &world, Player &player, const Merchant &merchant) override;

public:
  explicit CatalogCommand(int playerId) : MerchantCommand(playerId) {}
};

#endif // CATALOG_COMMAND_H_