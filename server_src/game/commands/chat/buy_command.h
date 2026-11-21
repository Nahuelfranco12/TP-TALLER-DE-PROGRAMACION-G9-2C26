#ifndef BUY_COMMAND_H_
#define BUY_COMMAND_H_

#include <string>

#include "merchant_command.h"

class BuyCommand : public MerchantCommand {
private:
  std::string args;

protected:
  void trade(World &world, Player &player, const Merchant &merchant) override;

public:
  BuyCommand(int playerId, const std::string &args)
      : MerchantCommand(playerId), args(args) {}
};

#endif // BUY_COMMAND_H_