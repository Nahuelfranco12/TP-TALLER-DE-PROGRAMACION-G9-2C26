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

std::unique_ptr<Command> CommandFactory::create(int player_id,
                                                const PlantDto &dto) {
  Position target(dto.target.x, dto.target.y);
  CropTypes crop = static_cast<CropTypes>(dto.crop);
  return std::make_unique<PlantCommand>(player_id, target, crop);
}

std::unique_ptr<Command> CommandFactory::create(int player_id,
                                                const GiftOfferDto &dto) {
  return std::make_unique<GiftOfferCommand>(player_id, dto.receiverId,
                                            dto.slotIndex);
}
std::unique_ptr<Command> CommandFactory::create(int player_id,
                                                const GiftResponseDto &dto) {
  return std::make_unique<GiftResponseCommand>(player_id, dto.accept);
}
std::unique_ptr<Command> CommandFactory::create(int player_id,
                                                const TillDto &dto) {
  return std::make_unique<TillCommand>(player_id, dto.direction);
}

std::unique_ptr<Command> CommandFactory::create(int player_id,
                                                const WaterDto &dto) {
  return std::make_unique<WaterCommand>(player_id, dto.direction);
}

std::unique_ptr<Command> CommandFactory::create(int player_id,
                                                const AttackDto &dto) {
  return std::make_unique<AttackCommand>(player_id, dto.direction);
}

std::unique_ptr<Command> CommandFactory::create(int player_id, const PlaceDto &dto) {
  return std::make_unique<PlaceCommand>(player_id, dto.slotIndex, dto.direction);
}

std::unique_ptr<Command>
CommandFactory::create_cheat_water(int player_id, const WaterDto &dto) {
  return std::make_unique<CheatWaterCropCommand>(player_id, dto.direction);
}

std::unique_ptr<Command> CommandFactory::create(int player_id,
                                                const ChatDto &dto) {
  const std::string &text = dto.text;
  if (text.empty() || text[0] != '/')
    return std::make_unique<ChatCommand>(player_id, text);

  size_t space = text.find(' ');
  bool hasArgs = space != std::string::npos;
  std::string word = hasArgs ? text.substr(0, space) : text;
  std::string args = hasArgs ? text.substr(space + 1) : "";

  if (word == "/consultar_catalogo")
    return std::make_unique<CatalogCommand>(player_id);
  if (word == "/comprar")
    return std::make_unique<BuyCommand>(player_id, args);
  if (word == "/vender")
    return std::make_unique<SellCommand>(player_id, args);
  if (word == "/vida")
    return std::make_unique<LifeCheatCommand>(player_id, args);
  if (word == "/energia")
    return std::make_unique<EnergyCheatCommand>(player_id, args);
  if (word == "/oro")
    return std::make_unique<GoldCheatCommand>(player_id, args);
  if (word == "/crecer")
    return create_cheat_growth(player_id);
  if (word == "/terminar_dia")
    return create_cheat_end_day(player_id);
  if (word == "/danio_enemigos")
    return create_cheat_enemies_damage(player_id);
  if (word == "/correr")
    return std::make_unique<RunCheatCommand>(player_id);
  return std::make_unique<UnknownCommand>(player_id, word);
}

std::unique_ptr<Command> CommandFactory::create(int player_id, const InteractDto &dto) {
  return std::make_unique<InteractCommand>(player_id, Position(dto.target.x, dto.target.y));
}

std::unique_ptr<Command> CommandFactory::create(int player_id, const ChestMoveDto &dto) {
  return std::make_unique<ChestMoveCommand>(player_id, dto.slotIndex, dto.toChest);
}

std::unique_ptr<Command> CommandFactory::create_cheat_growth(int player_id) {
  return std::make_unique<CheatGrowthCommand>(player_id);
}

std::unique_ptr<Command> CommandFactory::create_cheat_end_day(int player_id) {
  return std::make_unique<CheatEndDayCommand>(player_id);
}

std::unique_ptr<Command> CommandFactory::create_cheat_enemies_damage(int player_id) {
  return std::make_unique<CheatEnemiesDamageCommand>(player_id);
}

std::unique_ptr<Command>
CommandFactory::create_join(int player_id, const std::string &name,
                            const PlayerOutfitDto &outfit) {
  PlayerOutfit game_outfit(static_cast<PlayerHats>(outfit.hat),
                           static_cast<PlayerHairs>(outfit.hair),
                           static_cast<PlayerShirts>(outfit.tshirt),
                           static_cast<PlayerPants>(outfit.pants));
  return std::make_unique<JoinCommand>(player_id, name, game_outfit);
}

std::unique_ptr<Command> CommandFactory::create_confirm_day() {
  return std::make_unique<ConfirmDayCommand>();
}