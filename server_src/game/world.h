#ifndef WORLD_H_
#define WORLD_H_

#include <map>
#include <memory>

#include "../world_state.h"
#include "./entities/animal.h"
#include "./entities/player.h"
#include "./sectors/sector.h"
#include "game_constants.h"
#include "position.h"
#include "sectors/farm_sector.h"
#include "sectors/cabin_sector.h"
#include "entities/bed.h"

class World {
private:
  DaySpeed speed;
  std::map<IdSector, std::unique_ptr<Sector>> sectors;
  std::map<int, Player *> players;
  std::vector<ChatMessageState> chat;

  size_t dayTick;
  size_t dayNumber;

  Sector *findSectorOf(const Player *player);
  bool sendPlayerToFarm(Player *player, Sector &farm);
  void sendPlayersToFarm();
  void respawnNextTo(Player &player, Sector &sector, Position spot);

public:
  explicit World(DaySpeed speed) : speed(speed), dayTick(0), dayNumber(1) {}

  bool addSector(std::unique_ptr<Sector> sector);
  bool addDoor(IdSector idSectorOrigin, IdSector idSectorDestine,
               Position posOrigin, Position posDestine);

  bool createCabin(int playerId, Position top);

  /*
  * Entities
  */
  void addPlayer(int id, const std::string &name, PlayerOutfit outfit,
                 IdSector idSector);
  void removePlayer(int id);

  bool spawnMineral(IdSector sectorId, Position pos, MineralTypes type,
                    double freq, size_t pickaxeHits);
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


  bool allPlayersSleeping() const;

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
};

#endif // WORLD_H_
