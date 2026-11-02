#include "world.h"

#include <utility>

#include "entities/chicken.h"
#include "entities/cow.h"
#include "entities/mineral.h"

bool World::addSector(IdSector id, size_t width, size_t height) {
  auto [it, inserted] = this->sectors.try_emplace(id, width, height, id);
  return inserted;
}

void World::addPlayer(int id, PlayerOutfit outfit, IdSector idSector) {
  auto sectorIt = this->sectors.find(idSector);
  if (sectorIt == this->sectors.end())
    return;

  Sector &sector = sectorIt->second;
  Position startPos = sector.findFreePosition();

  auto player =
      std::make_unique<Player>(startPos.x, startPos.y, id, &sector, outfit);
  Player *playerPtr = player.get();

  if (!sector.addEntity(std::move(player), startPos))
    return;

  this->players.emplace(id, playerPtr);
}

void World::removePlayer(int id) { this->players.erase(id); }

bool World::spawnMineral(IdSector sectorId, Position pos, MineralTypes type,
                         double freq, MineralPickaxeTime pickaxeTime) {
  auto it = this->sectors.find(sectorId);
  if (it == this->sectors.end())
    return false;
  auto mineral =
      std::make_unique<Mineral>(pos.x, pos.y, type, freq, pickaxeTime);
  return it->second.addEntity(std::move(mineral), pos);
}

bool World::spawnAnimal(IdSector sectorId, Position pos, AnimalType type) {
  auto it = this->sectors.find(sectorId);
  if (it == this->sectors.end())
    return false;

  std::unique_ptr<Entity> animal;
  switch (type) {
  case AnimalType::COW:
    animal = std::make_unique<Cow>(pos.x, pos.y);
    break;
  case AnimalType::CHICKEN:
    animal = std::make_unique<Chicken>(pos.x, pos.y);
    break;
  default:
    return false;
  }
  return it->second.addEntity(std::move(animal), pos);
}

// cppcheck-suppress functionStatic
bool World::transfer(Entity & /*e*/, IdSector /*destine*/, Position /*pos*/) {
  // TODO: implementar transferencia entre sectores
  return false;
}

Player *World::getPlayer(int id) {
  auto it = this->players.find(id);
  return (it != this->players.end()) ? it->second : nullptr;
}

const std::map<int, Player *> World::getPlayers() const {
  return this->players;
}

Sector *World::getSector(IdSector id) {
  auto it = this->sectors.find(id);
  return (it != this->sectors.end()) ? &it->second : nullptr;
}

WorldState World::state() const {
  WorldState state;
  state.sectors.reserve(sectors.size());
  for (const auto &[id, sector] : sectors)
    state.sectors.push_back(sector.state());
  for (const auto &[id, player] : players)
    state.players.push_back(player->state());
  return state;
}
