#include "world.h"

#include <utility>

#include "entities/chicken.h"
#include "entities/cow.h"
#include "entities/enemies/enemies_factory.h"
#include "entities/mineral.h"
#include "entities/merchants_factory.h"

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

bool World::createCabin(int playerId, Position top) {
  if (playerId < 0 || playerId >= MAX_PLAYERS)
    return false;

  IdSector cabinId = cabinSectorId(playerId);
  if (this->sectors.count(cabinId))
    return true;

  auto *farm = dynamic_cast<FarmSector *>(this->getSector(IdSector::FARM));
  if (!farm)
    return false;

  auto b = farm->placeCabin(playerId, top);
  if (!b)
    return false;

  if (!this->addSector(std::make_unique<CabinSector>(playerId, cabinId)))
    return false;

  return this->addDoor(IdSector::FARM, cabinId, b->door,
                       Position(CABIN_ENTRY_X, CABIN_ENTRY_Y));
}

void World::addPlayer(int id, const std::string &name, PlayerOutfit outfit,
                      IdSector idSector) {
  auto sectorIt = this->sectors.find(idSector);
  if (sectorIt == this->sectors.end())
    return;
  
  // TODO: revisar porque se deben leer del archivo las posiciones de las cabañas
  if (!this->createCabin(id, Position(2 + 10 * id, 1)))
    return;

  Sector &sector = *sectorIt->second;
  Position startPos(0, 0);
  if (!sector.findFreePosition(startPos))
    return;

  std::unique_ptr<Entity> player = std::make_unique<Player>(
      startPos.x, startPos.y, id, name, &sector, outfit);
  Player *playerPtr = dynamic_cast<Player *>(player.get());

  if (!sector.tryAddEntity(player, startPos))
    return;

  this->players.emplace(id, playerPtr);
}

void World::removePlayer(int id) {
  Player *player = getPlayer(id);
  if (player) {
    Sector *sector = player->getActualSector();
    if (sector)
      sector->removeEntity(player->position);
  }
  this->players.erase(id);
}

bool World::spawnMineral(IdSector sectorId, Position pos, MineralTypes type,
                         double freq, size_t pickaxeHits) {
  auto it = this->sectors.find(sectorId);
  if (it == this->sectors.end())
    return false;
  std::unique_ptr<Entity> mineral =
      std::make_unique<Mineral>(pos.x, pos.y, type, freq, pickaxeHits);
  return it->second->tryAddEntity(mineral, pos);
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
  return it->second->tryAddEntity(animal, pos);
}

bool World::spawnMerchant(IdSector sectorId, Position pos, MerchantType type) {
  auto it = this->sectors.find(sectorId);
  if (it == this->sectors.end())
    return false;
    
  MerchantsFactory factory;
  std::unique_ptr<Entity> merchant = factory.create(type, pos);
  if (!merchant)
    return false;
  return it->second->tryAddEntity(merchant, pos);
}

bool World::spawnEnemy(IdSector sectorId, Position pos, EnemyType type) {
  auto it = this->sectors.find(sectorId);
  if (it == this->sectors.end())
    return false;

  EnemiesFactory factory;
  std::unique_ptr<Entity> enemy;
  switch (type) {
  case EnemyType::SKELETON:
    enemy = factory.createEnemy(type, pos);
    break;

  case EnemyType::ORC:
    enemy = factory.createEnemy(type, pos);
    break;

  case EnemyType::TRAP_FLAME:
    enemy = factory.createTrap(type, pos);
    break;

  case EnemyType::TRAP_PINCH:
    enemy = factory.createTrap(type, pos);
    break;

  case EnemyType::VAMPIRE_MALE:
  case EnemyType::VAMPIRE_FEMALE:
    return false;

  case EnemyType::SKULL_BLUE:
  case EnemyType::SKULL_GREEN:
    enemy = factory.createEnemy(type, pos);
    break;
  }

  if (!enemy)
    return false;
  return it->second->tryAddEntity(enemy, pos);
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

const Sector *World::getSector(IdSector id) const {
  auto it = this->sectors.find(id);
  return (it != this->sectors.end()) ? it->second.get() : nullptr;
}

void World::growthCheatAll() {
  for (auto &[id, sector] : sectors)
    sector->growthCheatAll();
}

bool World::allPlayersDoneForTheDay() const {
  if (players.empty())
    return false;

  for (const auto &[playerId, player] : players) {
    if(!player->isDoneForTheDay())
      return false;
  }
  return true;
}

void World::endDayCheat() {
  this->dayTick = TICKS_PER_DAY - 240;
}

void World::cavernCheat() {
  for (auto &[id, sectorPtr] : this->sectors) {
    sectorPtr->cheatEnemies();
  }
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
  state.chat = chat;
  return state;
}

void World::tick() {
  for (auto &[id, sector] : sectors) {
    sector->tick();
  }

  dayTick++;
  if (allPlayersDoneForTheDay() || dayTick >= TICKS_PER_DAY) {
    dayTick = 0;
    dayNumber++;
    // TODO: se debe invocar recien cuando todos los jugadores dan el OK (posible comando).
    endDay();
  }
}

Sector *World::findSectorOf(const Player *player) {
  for (auto &[id, sector] : this->sectors)
    if (sector->getEntity(player->position) == player)
      return sector.get();
  return nullptr;
}

bool World::sendPlayerToFarm(Player *player, Sector &farm) {
  Sector *origin = this->findSectorOf(player);
  if (origin == nullptr)
    return false;

  Position originPos = player->position;
  std::unique_ptr<Entity> entity = origin->removeEntity(originPos);
  if (!entity)
    return false;

  Position target(0, 0);
  if (!farm.findFreePosition(target)) {
    origin->tryAddEntity(entity, originPos);
    return false;
  }
  if (!farm.isEmpty(target)) {
    origin->tryAddEntity(entity, originPos);
    return false;
  }

  if (!farm.tryAddEntity(entity, target)) {
    origin->tryAddEntity(entity, originPos);
    return false;
  }
  player->setActualSector(&farm);
  player->startNewDay(true);
  return true;
}

void World::sendPlayersToFarm() {
  Sector *farm = this->getSector(IdSector::FARM);
  if (farm == nullptr)
    return;

  for (auto &[id, player] : this->players)
    this->sendPlayerToFarm(player, *farm);
}

void World::endDay() {
  for (auto &[playerId, player] : players) {
    bool slept = player->isSleeping();

    CabinSector *cabin = dynamic_cast<CabinSector *>(getSector(cabinSectorId(playerId)));
    if (!cabin)
      continue;

    Sector *bedSector = nullptr;
    Bed *ownBed = findBedOf(playerId, bedSector);
    if (ownBed) {
      respawnNextTo(*player, *bedSector, ownBed->position);
    } else {
      Sector *cabin = getSector(cabinSectorId(playerId));
      if (cabin)
        respawnNextTo(*player, *cabin, Position(CABIN_ENTRY_X, CABIN_ENTRY_Y));
    }

    player->startNewDay(slept);
  }
  for (auto &[id, sector] : sectors){
    sector->releaseBeds();
    sector->endDay();
  }
}

Bed *World::findBedOf(int playerId, Sector *&bedSector) {
  for (auto &[id, sector] : this->sectors) {
    Bed *bed = sector->findBedOf(playerId);
    if (bed) {
      bedSector = sector.get();
      return bed;
    }
  }
  return nullptr;
}

void World::respawnNextTo(Player &player, Sector &sector, Position spot) {
  Position spawn(0, 0);
  if (!sector.findFreeNextTo(spot, spawn))
    return;

  Sector *origin = player.getActualSector();
  std::unique_ptr<Entity> entity = origin->removeEntity(player.position);
  if (!entity)
    return;

  if (sector.tryAddEntity(entity, spawn))
    player.setActualSector(&sector);
  else
    origin->tryAddEntity(entity, player.position);
}

void World::addChat(const ChatMessageState &message) {
  chat.push_back(message);
}

void World::clearChat() { chat.clear(); }

Player *World::getPlayerByName(const std::string &name) {
  for (auto &[id, player] : this->players)
    if (player->getName() == name)
      return player;
  return nullptr;
}
