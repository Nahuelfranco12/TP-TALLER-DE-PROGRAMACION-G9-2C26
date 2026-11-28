#ifndef WORLD_STATE_H_
#define WORLD_STATE_H_

#include "game/game_constants.h"
#include "game/position.h"
#include "game/terrain.h"

#include <cstddef>
#include <cstdint>
#include <vector>

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

struct TerrainState {
  TerrainType type;
  TerrainDecoration decoration;
  bool transitable;
  bool arable;
  bool isDoor;
  DoorType doorType = VillageEntry;
  bool tilled = false;
};

struct BuildingState {
  BuildingType type;
  Position topLeft;
  size_t width;
  size_t height;
  Position door;
  IdSector interior;
  int ownerId;
};

struct CropState {
  CropTypes type{};

  size_t growthTicks{};
  size_t sinceWatered{};
  size_t thirstyTicks{};
  size_t readyTicks{};
  size_t extraHarvestsLeft{};
  double luck{};

  CropGrowth growth{};
  bool needsWater;
};

struct MineralState {
  MineralTypes type{};
  size_t remainingHits;
};

struct AnimalState {
  AnimalType type{};
  bool is_ready = false;
};

struct MerchantState {
  MerchantType type{};
};

struct FurnitureState {
  FurnitureType type{};
};

struct ChestState {
  InventoryState inventory;
  int openedBy = INVALID_PLAYER_ID;
};

struct EnemyState {
  EnemyType type{};
  bool is_alive = true;
  DirectionDto direction = DirectionDto::Up;
};

struct BedState {
  bool sleeping;
  int ownerId = INVALID_PLAYER_ID;
};

struct DoorState {
  DoorType type;
};

struct EntityState {
  EntityTypes type{};
  Position position;
  int playerId =
      INVALID_PLAYER_ID;  // INVALID_PLAYER_ID en caso de no ser jugador.
  MineralState mineral{}; // en caso de ser mineral.
  AnimalState animal{};   // en caso de ser animal.
  CropState crop{};       // en caso de ser mineral
  EnemyState enemy{};     // en caso de ser enemigo
  BedState bed{};
  DoorState door{};
  MerchantState merchant{}; // en caso de ser comerciante.
  FurnitureState furniture{}; // en caso de ser mueble
  ChestState chest{};         // en caso de ser cofre

  // TODO: cultivos y npcs
};

struct PlayerOutfitState {
  PlayerHats hat;
  PlayerHairs hairs;
  PlayerShirts tshirt;
  PlayerPants pants;
};

struct ChatMessageState {
  int fromId;
  std::string fromName;
  int toId;
  std::string text;
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
  int pendingGiftGiverId = 0;
  ItemState pendingGift{};
  DirectionDto facing{};
};

struct SetGoalState {
  int goal;
  size_t current;
  size_t target;
};

struct SetState {
  int type;
  bool completed;
  std::vector<SetGoalState> goals;
};

struct SectorState {
  IdSector id{};
  size_t width = 0;
  size_t height = 0;
  std::vector<std::vector<TerrainState>> tiles;
  std::vector<BuildingState> buildings;
  std::vector<EntityState> entities;
};

struct GameTime {
  size_t hours;
  size_t minutes;
};

struct WorldState {
  std::string name;
  std::string code;

  std::vector<SectorState> sectors;
  std::vector<PlayerState> players;
  size_t dayNumber = 1;
  GameTime time{6, 0};
  std::vector<ChatMessageState> chat;
  bool waitingNewDayConfirmation = false;
  std::vector<SetState> sets;
};

#endif // WORLD_STATE_H_
