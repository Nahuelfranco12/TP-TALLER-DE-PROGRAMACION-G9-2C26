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
  std::map<IdSector, Sector> sectors;
  std::map<int, Player *> players;

public:
  explicit World(DaySpeed speed) : speed(speed) {}

  bool addSector(IdSector id, size_t width = 30, size_t height = 30);

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
  SectorMapState mapState(IdSector id) const;
};

#endif // WORLD_H_
