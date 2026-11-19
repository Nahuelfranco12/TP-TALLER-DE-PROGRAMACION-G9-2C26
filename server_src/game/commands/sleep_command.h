#ifndef SLEEP_COMMAND_H_
#define SLEEP_COMMAND_H_

#include "../command.h"

class SleepCommand : public Command {
private:
  int playerId;

public:
  explicit SleepCommand(int playerId) : playerId(playerId) {}

  void execute(World &world) override;
};

#endif // SLEEP_COMMAND_H_
