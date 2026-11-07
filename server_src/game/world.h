#ifndef WORLD_H_
#define WORLD_H_

#include <map>
#include <memory>

#include "../world_state.h"
#include "./entities/animal.h"
#include "./entities/player.h"
#include "game_constants.h"
#include "position.h"
#include "sector.h"

class World {
private:
  DaySpeed speed;
  std::map<IdSector, std::unique_ptr<Sector>> sectors;
  std::map<int, Player *> players;

  size_t dayTick;
  size_t dayNumber;

public:
  explicit World(DaySpeed speed) : speed(speed), dayTick(0), dayNumber(1) {}

  bool addSector(std::unique_ptr<Sector> sector);
  bool addDoor(IdSector idSectorOrigin, IdSector idSectorDestine,
               Position posOrigin, Position posDestine);

  void addPlayer(int id, PlayerOutfit outfit, IdSector idSector);
  void removePlayer(int id);

  bool spawnMineral(IdSector sectorId, Position pos, MineralTypes type,
                    double freq, MineralPickaxeTime pickaxeTime);
  bool spawnAnimal(IdSector sectorId, Position pos, AnimalType type);

  // TODO: implementar con puertas
  bool transfer(Entity &e, IdSector destine, Position pos);

  Player *getPlayer(int id);
  const std::map<int, Player *> getPlayers() const;

  Sector *getSector(IdSector id);

  WorldState state() const;

  void tick();
  void endDay();
};

#endif // WORLD_H_
