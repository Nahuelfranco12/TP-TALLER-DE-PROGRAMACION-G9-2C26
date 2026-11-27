#ifndef CONFIRM_DAY_COMMAND_H_
#define CONFIRM_DAY_COMMAND_H_

#include "../command.h"
#include "../world.h"

class ConfirmDayCommand : public Command {
public:
  void execute(World &world) override { world.addADayConfirmation(); }
};

#endif // CONFIRM_DAY_COMMAND_H_