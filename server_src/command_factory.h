#ifndef COMMAND_FACTORY_H_
#define COMMAND_FACTORY_H_

#include <memory>

#include "../common_src/game_dtos.h"

#include "./game/command.h"

#include "./game/commands/attack_command.h"
#include "./game/commands/chat_command.h"
#include "./game/commands/collect_command.h"
#include "./game/commands/gift_offer_command.h"
#include "./game/commands/gift_response_command.h"
#include "./game/commands/mine_command.h"
#include "./game/commands/move_command.h"
#include "./game/commands/plant_command.h"
#include "./game/commands/select_tool_command.h"
#include "./game/commands/till_command.h"
#include "./game/commands/water_command.h"
#include "./game/commands/interact_command.h"
#include "./game/commands/place_command.h"

#include "./game/commands/cheats/cheat_growth_command.h"
#include "./game/commands/cheats/cheat_water_crop_command.h"
#include "./game/commands/cheats/cheat_end_day_command.h"
#include "./game/commands/cheats/cheat_enemies_damage_command.h"

#include "./game/commands/chat/buy_command.h"
#include "./game/commands/chat/catalog_command.h"
#include "./game/commands/chat/sell_command.h"
#include "./game/commands/chat/unknown_command.h"

class CommandFactory {
public:
  std::unique_ptr<Command> create(int player_id, const MoveDto &dto);
  std::unique_ptr<Command> create(int player_id, const MineDto &dto);
  std::unique_ptr<Command> create(int player_id, const ToolTypeDto &dto);
  std::unique_ptr<Command> create(int player_id, const CollectDto &dto);
  std::unique_ptr<Command> create(int player_id, const PlantDto &dto);
  std::unique_ptr<Command> create(int player_id, const GiftOfferDto &dto);
  std::unique_ptr<Command> create(int player_id, const GiftResponseDto &dto);
  std::unique_ptr<Command> create(int player_id, const TillDto &dto);
  std::unique_ptr<Command> create(int player_id, const WaterDto &dto);
  std::unique_ptr<Command> create(int player_id, const AttackDto &dto);
  std::unique_ptr<Command> create(int player_id, const ChatDto &dto);
  std::unique_ptr<Command> create(int player_id, const InteractDto &dto);
  std::unique_ptr<Command> create(int player_id, const PlaceDto &dto);
  std::unique_ptr<Command> create_join(int player_id, const std::string &name,
                                       const PlayerOutfitDto &outfit);
  std::unique_ptr<Command> create_cheat_water(int player_id,
                                              const WaterDto &dto);
  std::unique_ptr<Command> create_cheat_growth(int player_id);
  std::unique_ptr<Command> create_cheat_end_day(int player_id);
std::unique_ptr<Command> create_cheat_enemies_damage(int player_id);
};

#endif // COMMAND_FACTORY_H_
