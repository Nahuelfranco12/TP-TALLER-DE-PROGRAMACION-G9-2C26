#ifndef CHEAT_END_DAY_H_COMMAND_H_
#define CHEAT_END_DAY_H_COMMAND_H_

#include "../../../../common_src/game_dtos.h"
#include "../../command.h"

class CheatEndDayCommand : public Command {
private:
  int playerId;

public:
  CheatEndDayCommand(int playerId) : playerId(playerId) {}

  void execute(World &world) override;
};

#endif // CHEAT_END_DAY_H_COMMAND_H_
