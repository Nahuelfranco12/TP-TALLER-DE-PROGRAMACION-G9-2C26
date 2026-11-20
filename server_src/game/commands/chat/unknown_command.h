#ifndef UNKNOWN_COMMAND_H_
#define UNKNOWN_COMMAND_H_

#include <string>

#include "../../command.h"

class UnknownCommand : public Command {
private:
  int playerId;
  std::string word;

public:
  UnknownCommand(int playerId, const std::string &word);
  void execute(World &world) override;
};

#endif // UNKNOWN_COMMAND_H_