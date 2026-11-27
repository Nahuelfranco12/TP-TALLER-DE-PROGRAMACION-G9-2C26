#ifndef REDEEM_SET_COMMAND_H_
#define REDEEM_SET_COMMAND_H_

#include "../command.h"
#include "../position.h"

class RedeemSetCommand : public Command {
private:
  int playerId;
  int setIndex;
  int slotIndex;
  int amount;

public:
  RedeemSetCommand(int playerId, int setIndex, int slotIndex, int amount)
      : playerId(playerId), setIndex(setIndex), slotIndex(slotIndex),
        amount(amount) {}

  void execute(World &world) override;
};

#endif // REDEEM_SET_COMMAND_H_