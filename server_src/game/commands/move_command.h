#ifndef MOVE_COMMAND_H_
#define MOVE_COMMAND_H_

#include "../../../common_src/game_dtos.h"
#include "../command.h"
#include "../position.h"

class MoveCommand : public Command {
private:
  int playerId;
  DirectionDto direction;

public:
  MoveCommand(int playerId, DirectionDto direction)
      : playerId(playerId), direction(direction) {}

  void execute(World &world) override;
};

#endif // MOVE_COMMAND_H_
