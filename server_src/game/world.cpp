#include "world.h"

#include <utility>

#include "entities/chicken.h"
#include "entities/cow.h"
#include "entities/mineral.h"

bool World::addSector(std::unique_ptr<Sector> sector) {
  IdSector id = sector->getId();
  auto [it, inserted] = this->sectors.try_emplace(id, std::move(sector));
  return inserted;
}

bool World::addDoor(IdSector idSectorOrigin, IdSector idSectorDestine,
                    Position posOrigin, Position posDestine) {
  auto sectorOriginIt = this->sectors.find(idSectorOrigin);
  auto sectorDestineIt = this->sectors.find(idSectorDestine);

  if (sectorOriginIt == this->sectors.end() ||
      sectorDestineIt == this->sectors.end())
    return false;

  Sector &sectorOrigin = *sectorOriginIt->second;
  Sector &sectorDestine = *sectorDestineIt->second;

  bool doorOrigin =
      sectorOrigin.addDoor(std::make_unique<Door>(posOrigin, idSectorDestine,
                                                  sectorDestine, posDestine),
                           posOrigin);
  bool doorDestine =
      sectorDestine.addDoor(std::make_unique<Door>(posDestine, idSectorOrigin,
                                                   sectorOrigin, posOrigin),
                            posDestine);

  return doorOrigin && doorDestine;
}

void World::addPlayer(int id, PlayerOutfit outfit, IdSector idSector) {
  auto sectorIt = this->sectors.find(idSector);
  if (sectorIt == this->sectors.end())
    return;

  Sector &sector = *sectorIt->second;
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
                         double freq, size_t pickaxeHits) {
  auto it = this->sectors.find(sectorId);
  if (it == this->sectors.end())
    return false;
  auto mineral =
      std::make_unique<Mineral>(pos.x, pos.y, type, freq, pickaxeHits);
  return it->second->addEntity(std::move(mineral), pos);
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
  return it->second->addEntity(std::move(animal), pos);
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
  return (it != this->sectors.end()) ? it->second.get() : nullptr;
}

GameTime World::currentTime() const {
  size_t GAME_TOTAL_MINUTES = DAY_DURATION_HOUR * 60;
  
  size_t gameMinutes = (dayTick * GAME_TOTAL_MINUTES) / TICKS_PER_DAY;
  size_t quantized = (gameMinutes / TIME_INTERVAL) * TIME_INTERVAL;

  size_t absoluteMinutes = DAY_START_HOUR * 60 + quantized;
  return {(absoluteMinutes / 60) % 24, absoluteMinutes % 60};
}

WorldState World::state() const {
  WorldState state;
  state.sectors.reserve(sectors.size());

  for (const auto &[id, sector] : sectors)
    state.sectors.push_back(sector->state());

  for (const auto &[id, player] : players)
    state.players.push_back(player->state());

  state.dayNumber = dayNumber;
  state.time = currentTime();

  return state;
}

void World::tick() {
  for (auto &[id, sector] : sectors) {
    sector->tick();
  }

  dayTick++;
  if (dayTick >= TICKS_PER_DAY) {
    dayTick = 0;
    dayNumber++;
    endDay();
  }
}

void World::endDay() {
  for (auto &[id, sector] : sectors)
    sector->endDay();
}
