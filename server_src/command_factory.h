#ifndef COMMAND_FACTORY_H_
#define COMMAND_FACTORY_H_

#include <memory>

#include "../common_src/game_dtos.h"
#include "./game/command.h"
#include "./game/commands/collect_command.h"
#include "./game/commands/mine_command.h"
#include "./game/commands/move_command.h"
#include "./game/commands/select_tool_command.h"

class CommandFactory {
public:
  std::unique_ptr<Command> create(int player_id, const MoveDto &dto);
  std::unique_ptr<Command> create(int player_id, const MineDto &dto);
  std::unique_ptr<Command> create(int player_id, const ToolTypeDto &dto);
  std::unique_ptr<Command> create(int player_id, const CollectDto &dto);
  std::unique_ptr<Command> create_join(int player_id,
                                       const PlayerOutfitDto &outfit);
};

#endif // COMMAND_FACTORY_H_
