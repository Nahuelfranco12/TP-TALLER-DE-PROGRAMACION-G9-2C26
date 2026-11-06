#ifndef WORLD_STATE_H_
#define WORLD_STATE_H_

#include "game/game_constants.h"
#include "game/position.h"
#include "game/terrain.h"

#include <cstddef>
#include <cstdint>
#include <vector>

struct TerrainState {
  TerrainType type;
  bool transitable;
  bool arable;
  bool isDoor;
};

struct EntityState {
  EntityTypes type{};
  Position position;
  int playerId =
      INVALID_PLAYER_ID;      // INVALID_PLAYER_ID en caso de no ser jugador.
  MineralTypes mineralType{}; // en caso de ser mineral.
  AnimalType animalType{};    // en caso de ser animal.
  bool is_ready = true;

  // TODO: cultivos y npcs
};

struct ItemState {
  ItemType type;
  int subtype; // MineralTypes/AnimalTypes/SeedTypes casteado, 0 en caso
               // contrario
  int count;
};

struct ToolState {
  AvailableTools type;
};

struct InventoryState {
  std::vector<ItemState> items;
  std::vector<ToolState> tools;
};

struct PlayerOutfitState {
  PlayerHats hat;
  PlayerHairs hairs;
  PlayerShirts tshirt;
  PlayerPants pants;
};

struct PlayerState {
  int id = 0;
  Position position;
  double life = 0.0;
  double energy = 0.0;
  int coins = 0;
  IdSector sector{};

  PlayerOutfitState outfit{};
  AvailableTools actualTool{};

  InventoryState inventory;
};

struct SectorState {
  IdSector id{};
  size_t width = 0;
  size_t height = 0;
  std::vector<std::vector<TerrainState>> tiles;
  std::vector<EntityState> entities;
};

struct WorldState {
  std::vector<SectorState> sectors;
  std::vector<PlayerState> players;
};

#endif // WORLD_STATE_H_
