#include "command_factory.h"

#include <memory>

#include "./game/commands/join_command.h"

std::unique_ptr<Command> CommandFactory::create(int player_id,
                                                const MoveDto &dto) {
  return std::make_unique<MoveCommand>(player_id, dto.direction);
}

std::unique_ptr<Command> CommandFactory::create(int player_id,
                                                const MineDto &dto) {
  return std::make_unique<MineCommand>(player_id, dto.direction);
}

std::unique_ptr<Command> CommandFactory::create(int player_id,
                                                const ToolTypeDto &dto) {
  return std::make_unique<SelectToolCommand>(player_id,
                                             static_cast<AvailableTools>(dto));
}

std::unique_ptr<Command> CommandFactory::create(int player_id,
                                                const CollectDto &dto) {
  return std::make_unique<CollectCommand>(player_id, dto.direction);
}

std::unique_ptr<Command> CommandFactory::create(int player_id, const PlantDto &dto) {
    Position target(dto.target.x, dto.target.y);
    CropTypes crop = static_cast<CropTypes>(dto.crop);
    return std::make_unique<PlantCommand>(player_id, target, crop);
}

std::unique_ptr<Command> create(int player_id, const TillDto &dto) {
  return std::make_unique<TillCommand>(player_id, dto.direction);
}

std::unique_ptr<Command>
CommandFactory::create_join(int player_id, const PlayerOutfitDto &outfit) {
  PlayerOutfit game_outfit(static_cast<PlayerHats>(outfit.hat),
                           static_cast<PlayerHairs>(outfit.hair),
                           static_cast<PlayerShirts>(outfit.tshirt),
                           static_cast<PlayerPants>(outfit.pants));
  return std::make_unique<JoinCommand>(player_id, game_outfit);
}
