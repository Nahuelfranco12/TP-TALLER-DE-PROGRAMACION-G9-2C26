#ifndef CHEST_MOVE_COMMAND_H_
#define CHEST_MOVE_COMMAND_H_

#include "../command.h"

class ChestMoveCommand : public Command {
private:
  int playerId;
  int slotIndex;
  bool toChest;

public:
  ChestMoveCommand(int playerId, int slotIndex, bool toChest)
      : playerId(playerId), slotIndex(slotIndex), toChest(toChest) {}
  void execute(World &world) override;
};

#endif // CHEST_MOVE_COMMAND_H_