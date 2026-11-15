#ifndef GIFT_RESPONSE_COMMAND_H
#define GIFT_RESPONSE_COMMAND_H
#include "../command.h"

class GiftResponseCommand : public Command {
private:
  int receiverId;
  bool accept;

public:
  GiftResponseCommand(int receiverId, bool accept)
      : receiverId(receiverId), accept(accept) {}
  void execute(World &world) override;
};
#endif