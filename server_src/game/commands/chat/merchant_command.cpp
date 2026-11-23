#include "merchant_command.h"

#include "../../../../common_src/constants.h"
#include "../../entities/merchant.h"
#include "../../world.h"

void MerchantCommand::execute(World &world) {
  Player *player = world.getPlayer(playerId);
  if (!player)
    return;

  Merchant *merchant = player->getTalkingTo();
  if (!merchant) {
    world.addChat({SYSTEM_SENDER_ID, SYSTEM_SENDER_NAME, playerId, "No estás hablando con nadie. Hacé click en un comerciante!"});
    return;
  }

  bool inVillage = player->getActualSector()->getId() == IdSector::VILLAGE;
  if (!inVillage || player->position.distanceTo(merchant->position) > INTERACT_DISTANCE) {
    world.addChat({SYSTEM_SENDER_ID, SYSTEM_SENDER_NAME, playerId,  "Acercate a " + merchant->getName() + " para hablarle"});
    return;
  }

  trade(world, *player, *merchant);
}

void MerchantCommand::reply(World &world, const Merchant &merchant, const std::string &message) const {
  world.addChat({SYSTEM_SENDER_ID, merchant.getName(), playerId, message});
}

bool MerchantCommand::readProductAndAmount(const std::string &args, std::string &productName, int &amount) const {
  size_t space = args.find(' ');
  bool hasAmount = space != std::string::npos;
  productName = hasAmount ? args.substr(0, space) : args;
  std::string amountText = hasAmount ? args.substr(space + 1) : "1";

  if (productName.empty() || amountText.empty() || amountText.size() > 3)
    return false;
    
  for (char c : amountText)
    if (c < '0' || c > '9')
      return false;

  amount = std::stoi(amountText);
  return amount > 0;
}