#ifndef TILL_COMMAND_H
#define TILL_COMMAND_H

#include "../../../common_src/game_dtos.h"
#include "../command.h"

class TillCommand : public Command {
private:
  int playerId;
  DirectionDto direction;

public:
  TillCommand(int playerId, DirectionDto direction)
      : playerId(playerId), direction(direction) {}
  void execute(World &world) override;
};

#endif