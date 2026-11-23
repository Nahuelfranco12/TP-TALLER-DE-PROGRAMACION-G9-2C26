#ifndef MINE_COMMAND_H_
#define MINE_COMMAND_H_

#include "../../../common_src/game_dtos.h"
#include "../command.h"
#include "../position.h"

class MineCommand : public Command {
private:
  int playerId;
  DirectionDto direction;

public:
  MineCommand(int playerId, DirectionDto direction)
      : playerId(playerId), direction(direction) {}

  void execute(World &world) override;
};

#endif // MINE_COMMAND_H_
