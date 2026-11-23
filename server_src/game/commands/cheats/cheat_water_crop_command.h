#ifndef CHEAT_WATER_CROP_H_COMMAND_H_
#define CHEAT_WATER_CROP_H_COMMAND_H_

#include "../../../../common_src/game_dtos.h"
#include "../../command.h"

class CheatWaterCropCommand : public Command {
private:
  int playerId;
  DirectionDto direction;

public:
  CheatWaterCropCommand(int playerId, DirectionDto direction)
      : playerId(playerId), direction(direction) {}

  void execute(World &world) override;
};

#endif // CHEAT_WATER_CROP_H_COMMAND_H_
