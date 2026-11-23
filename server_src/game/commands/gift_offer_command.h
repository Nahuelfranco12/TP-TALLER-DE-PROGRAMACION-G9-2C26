#ifndef GIFT_OFFER_COMMAND_H
#define GIFT_OFFER_COMMAND_H
#include "../command.h"

class GiftOfferCommand : public Command {
private:
  int giverId;
  int receiverId;
  int slotIndex;

public:
  GiftOfferCommand(int giverId, int receiverId, int slotIndex)
      : giverId(giverId), receiverId(receiverId), slotIndex(slotIndex) {}
  void execute(World &world) override;
};
#endif