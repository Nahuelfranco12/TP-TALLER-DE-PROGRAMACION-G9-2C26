#ifndef PLACE_COMMAND_H_
#define PLACE_COMMAND_H_

#include "../command.h"

class PlaceCommand : public Command {
private:
  int playerId;
  int slotIndex;
  DirectionDto direction;

public:
  PlaceCommand(int playerId, int slotIndex, DirectionDto direction)
      : playerId(playerId), slotIndex(slotIndex), direction(direction) {}
  void execute(World &world) override;
};

#endif // PLACE_COMMAND_H_