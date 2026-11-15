#ifndef ATTACK_COMMAND_H_
#define ATTACK_COMMAND_H_

#include "../../../common_src/game_dtos.h"
#include "../command.h"
#include "../position.h"

class AttackCommand : public Command {
private:
  int playerId;
  DirectionDto direction;

public:
  AttackCommand(int playerId, DirectionDto direction)
      : playerId(playerId), direction(direction) {}

  void execute(World &world) override;
};

#endif // ATTACK_COMMAND_H_
