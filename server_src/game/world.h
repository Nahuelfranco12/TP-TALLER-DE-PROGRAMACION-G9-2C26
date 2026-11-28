#ifndef WORLD_H_
#define WORLD_H_

#include <map>
#include <memory>
#include <set>
#include <string>

#include "../world_state.h"
#include "./entities/animal.h"
#include "./entities/player.h"
#include "./sectors/sector.h"
#include "game_constants.h"
#include "position.h"
#include "sectors/farm_sector.h"
#include "sectors/cabin_sector.h"
#include "entities/bed.h"
#include "sets/set.h"
#include "sets/set_animal.h"
#include "sets/set_crop.h"
#include "sets/set_fight.h"
#include "sets/set_gold.h"
#include "sets/set_metal.h"

class World {
private:
  std::string name;
  std::string code;
  DaySpeed speed;
  std::map<IdSector, std::unique_ptr<Sector>> sectors;
  std::map<int, Player *> players;
  std::vector<ChatMessageState> chat;
  std::vector<std::unique_ptr<Set>> sets;

  size_t dayTick;
  size_t dayNumber;

  Sector *findSectorOf(const Player *player);
  bool sendPlayerToFarm(Player *player, Sector &farm);
  void sendPlayersToFarm();
  void respawnNextTo(Player &player, Sector &sector, Position spot);

public:
  explicit World(const std::string& name, const std::string& code, size_t dayNumber = 1)
      : name(name), code(code), speed(DaySpeed::MEDIUM), dayTick(0), dayNumber(dayNumber) {
    sets.push_back(std::make_unique<SetCrop>());
    sets.push_back(std::make_unique<SetMetal>());
    sets.push_back(std::make_unique<SetAnimal>());
    sets.push_back(std::make_unique<SetFight>());
    sets.push_back(std::make_unique<SetGold>());
  }

  void setDayNumber(size_t dayNumber) { this->dayNumber = dayNumber; }

  bool addSector(std::unique_ptr<Sector> sector);
  bool addDoor(IdSector idSectorOrigin, IdSector idSectorDestine,
               Position posOrigin, Position posDestine,
               DoorType typeOrigin = DoorType::VillageEntry,
               DoorType typeDestine = DoorType::VillageEntry);

  bool createCabin(int playerId, Position top);

  /*
  * Entities
  */
  void addPlayer(int id, const std::string &name, PlayerOutfit outfit,
                 IdSector idSector);
  void removePlayer(int id);
  bool spawnAnimal(IdSector sectorId, Position pos, AnimalType type);
  bool spawnEnemy(IdSector sectorId, Position pos, EnemyType type);
  bool spawnMerchant(IdSector sectorId, Position pos, MerchantType type);

  /*
  * getters
  */
  Player *getPlayer(int id);
  const std::map<int, Player *> getPlayers() const;
  Sector *getSector(IdSector id);
  const Sector *getSector(IdSector id) const;

  /*
  * Cheats
  */
  void growthCheatAll();
  void endDayCheat();
  void cavernCheat();


  bool allPlayersDoneForTheDay() const;

  /*
  * Chat
  */
  void addChat(const ChatMessageState &message);
  void clearChat();
  Player *getPlayerByName(const std::string &name);

  void tick();
  void endDay();
  Bed *findBedOf(int playerId, Sector *&bedSector);

  /*
  * State
  */
  GameTime currentTime() const;
  WorldState state() const;
  const std::vector<std::unique_ptr<Set>> &getSets() const { return sets; }
  void recordProgress(GoalTypes goal, size_t count);
  void applySetReward(SetType type);
  std::set<SetType> rewardedSets;
};

#endif // WORLD_H_
