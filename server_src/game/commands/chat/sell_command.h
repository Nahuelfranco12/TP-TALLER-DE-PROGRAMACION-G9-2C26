#ifndef SELL_COMMAND_H_
#define SELL_COMMAND_H_

#include <string>

#include "merchant_command.h"

class SellCommand : public MerchantCommand {
private:
  std::string args;

protected:
  void trade(World &world, Player &player, const Merchant &merchant) override;

public:
  SellCommand(int playerId, const std::string &args)
      : MerchantCommand(playerId), args(args) {}
};

#endif // SELL_COMMAND_H_