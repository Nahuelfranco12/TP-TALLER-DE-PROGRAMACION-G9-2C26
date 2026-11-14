#ifndef WATER_COMMAND_H_
#define WATER_COMMAND_H_

#include "../../../common_src/game_dtos.h"
#include "../command.h"

class WaterCommand : public Command {
private:
  int playerId;
  DirectionDto direction;

public:
  WaterCommand(int playerId, DirectionDto direction)
      : playerId(playerId), direction(direction) {}

  void execute(World &world) override;
};

#endif // WATER_COMMAND_H_
