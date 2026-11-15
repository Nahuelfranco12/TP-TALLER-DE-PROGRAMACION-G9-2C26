#ifndef CHAT_COMMAND_H_
#define CHAT_COMMAND_H_

#include <string>

#include "../command.h"

class ChatCommand : public Command {
private:
  int playerId;
  std::string text;

public:
  ChatCommand(int playerId, const std::string &text) : playerId(playerId), text(text) {}
  void execute(World &world) override;
};

#endif // CHAT_COMMAND_H_