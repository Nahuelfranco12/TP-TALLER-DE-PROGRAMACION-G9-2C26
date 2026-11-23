#ifndef INTERACT_COMMAND_H_
#define INTERACT_COMMAND_H_

#include "../position.h"
#include "../command.h"

class InteractCommand : public Command {
private:
  int playerId;
  Position target;

public:
  InteractCommand(int playerId, Position target)
      : playerId(playerId), target(target) {}

  void execute(World &world) override;
};

#endif // INTERACT_COMMAND_H_