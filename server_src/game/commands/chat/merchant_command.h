#ifndef MERCHANT_COMMAND_H_
#define MERCHANT_COMMAND_H_

#include <string>

#include "../../command.h"

class Merchant;
class Player;

class MerchantCommand : public Command {
protected:
  int playerId;

  virtual void trade(World &world, Player &player, const Merchant &merchant) = 0;

  void reply(World &world, const Merchant &merchant, const std::string &message) const;

  /*
  * Dado un string de argumentos, guarda el nombre del producto en "productName" y la cantidad en "amount"
  */
  bool readProductAndAmount(const std::string &args, std::string &productName, int &amount) const;

public:
  explicit MerchantCommand(int playerId) : playerId(playerId) {}
  void execute(World &world) override;
};

#endif // MERCHANT_COMMAND_H_