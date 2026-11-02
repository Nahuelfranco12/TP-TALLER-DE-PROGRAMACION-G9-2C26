#ifndef SELECT_TOOL_COMMAND_H_
#define SELECT_TOOL_COMMAND_H_

#include "../../../common_src/game_dtos.h"
#include "../command.h"
#include "../position.h"

class SelectToolCommand : public Command {
private:
  int playerId;
  AvailableTools tool;

public:
  SelectToolCommand(int playerId, AvailableTools tool)
      : playerId(playerId), tool(tool) {}

  void execute(World &world) override;
};

#endif // SELECT_TOOL_COMMAND_H_
