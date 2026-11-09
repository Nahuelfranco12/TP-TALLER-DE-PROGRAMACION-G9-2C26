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
  bool tilled = false;
};

struct CropState {
  CropTypes type{};
  CropGrowth growth{};
};

struct MineralState {
  MineralTypes type{};
};

struct AnimalState {
  AnimalType type{};
  bool is_ready = false;
};

struct EntityState {
  EntityTypes type{};
  Position position;
  int playerId =
      INVALID_PLAYER_ID;      // INVALID_PLAYER_ID en caso de no ser jugador.
  MineralState mineral{}; // en caso de ser mineral.
  AnimalState animal{};    // en caso de ser animal.
  CropState crop{}; // en caso de ser mineral

  // TODO: cultivos y npcs
};

struct ItemState {
  ItemType type;
  int subtype; // MineralTypes/AnimalTypes/SeedTypes casteado, 0 en caso
               // contrario
  int count;
  CropQuality quality{};
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

struct GameTime {
  size_t hours;
  size_t minutes;
};

struct WorldState {
  std::vector<SectorState> sectors;
  std::vector<PlayerState> players;
  size_t dayNumber = 1;
  GameTime time{6, 0};
};

#endif // WORLD_STATE_H_
