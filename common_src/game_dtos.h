#ifndef DTOS_H_
#define DTOS_H_

#include <cstddef>
#include <cstdint>
#include <list>
#include <map>
#include <string>
#include <vector>

enum class DirectionDto { Up, Down, Left, Right };
enum class TerrainTypeDto {
  DIRT,
  GRASS,
  GROUND
}; // TODO: en principio puerta es parte del enum (por si se quiere mostrar
   // distinto)
enum class SectorTypeDto { FARM, VILLAGE, CAVERN };

// TODO: revisar para que sea acorde a SDL
enum PlayerHatsDto {
  CAP_HAT,
  FARMER_HAT,
  LEAF_HAT,
  CHEF_HAT,
  CROWN_HAT,
  BOWTIE_HAT
}; // 6
enum PlayerHairsDto {
  CURLY_HAIR,
  STRAIGHT_HAIR,
  STRAIGHT_SHORT_HAIR,
  CURLY_SHORT_HAIR,
  AFRO_HAIR,
  EMO_HAIR
}; // 6
enum PlayerTShirtsDto {
  BLUE_SHIRT,
  WHITE_SHIRT,
  PINK_SHIRT,
  PURPLE_SHIRT,
  GREE_SHIRT
}; // 5
enum PlayerPantsDto {
  JEANS_PANTS,
  SKIRT_PANTS,
  FARMER_PANTS,
  FARMER_SHORT_PANTS
}; // 4

struct PlayerOutfitDto {
  PlayerHatsDto hat;
  PlayerHairsDto hair;
  PlayerTShirtsDto tshirt;
  PlayerPantsDto pants;
};

enum class ItemTypeDto {
  MINERAL_GOLD,
  MINERAL_IRON,
  MINERAL_LAPIZLAZULI,
  MINERAL_COAL,
  SEED,
  CHICKEN_EGG,
  COW_MILK,
  SEED_STRAWBERRY,
  SEED_GREEN_ONION,
  SEED_POTATO,
  SEED_PUMPKIN,
  CROP_STRAWBERRY,
  CROP_GREEN_ONION,
  CROP_POTATO,
  CROP_PUMPKIN,
};

enum class ToolTypeDto { SWORD, PICKAXE, SHOVEL, WATERING_CAN };

enum class EntityTypeDto {
  PLAYER,
  COW,
  CHICKEN,
  SKELETON,
  MINERAL_GOLD,
  MINERAL_IRON,
  MINERAL_LAPIZLAZULI,
  MINERAL_COAL,
  CROP,

  // TODO: resto de enemigos
  // TODO: NPCs del pueblo
};

enum class CropTypeDto { STRAWBERRY, GREEN_ONION, POTATO, PUMPKIN };

enum class CropGrowthDto { SEED_STAGE, EARLY_GROWTH, MID_GROWTH, FULL_GROWTH };

enum class CropQualityDto { BASE, GOOD, EXCELENT, INCREDIBLE, PERFECT };

struct MoveDto {
  DirectionDto direction = DirectionDto::Up;
};

struct MineDto {
  DirectionDto direction = DirectionDto::Up;
};

struct CollectDto {
  DirectionDto direction = DirectionDto::Up;
};

struct TillDto {
  DirectionDto direction = DirectionDto::Up;
};

struct WaterDto {
  DirectionDto direction = DirectionDto::Up;
};

// TODO: ver de eliminarlo
struct PlayerPositionDto {
  int id = 0;
  int x = 0;
  int y = 0;
};

struct GamePositionDto {
  size_t x = 0;
  size_t y = 0;

  bool operator<(const GamePositionDto &o) const {
    return x != o.x ? x < o.x : y < o.y;
  }
};

struct PlantDto {
  GamePositionDto target;
  CropTypeDto crop{};
};

struct TileDto {
  TerrainTypeDto type;
  bool transitable;
  bool arable;
  bool isDoor;
  bool tilled;
};

struct InventorySlotDto {
  int count = 0;
  ItemTypeDto item;
  CropQualityDto quality{};
};

struct GiftOfferDto {
  int receiverId = 0;
  int slotIndex = 0;
};

struct PendingGiftDto {
  int giverId = 0;
  InventorySlotDto gift; 
};

struct GiftResponseDto {
  bool accept = false;
};

struct InventoryDto {
  size_t ownerId = 0;

  std::list<InventorySlotDto> slots;
  std::list<ToolTypeDto> tools;
};

struct PlayerDto {
  size_t id = 0;

  PlayerOutfitDto outfit{};

  double life = 0.0;
  double energy = 0.0;
  size_t coins = 0;

  ToolTypeDto actualTool{};

  std::list<InventoryDto> inventory;
  PendingGiftDto pendingGift;
};

struct MineralDto {
  size_t remainingHits;
};

struct CropDto {
    CropTypeDto type{};
    CropGrowthDto growth{};
};

struct EntityDto {
  EntityTypeDto type{};
  bool ready = false; // x ahora solo se usa si es animal
  MineralDto mineral{}; // Solo se usa si es mineral
  CropDto crop{}; // Solo se usa si es cultivo
};

struct GameTimeDto {
  size_t hours = 6;
  size_t minutes = 0;
};

struct SectorStateDto {
  SectorTypeDto type{};
  size_t width = 0;
  size_t height = 0;

  std::vector<std::vector<TileDto>> sector;
  std::map<GamePositionDto, PlayerDto> players;
  std::map<GamePositionDto, EntityDto> entities;

  GameTimeDto time{};
  size_t dayNumber = 1;
};

struct WorldMapDto {
  std::vector<SectorStateDto> sectors;
};

// TODO: revisar para cuando se necesita mostrar el mapa completo
struct WorldStateDto {
  std::list<SectorStateDto> world;
  std::list<PlayerDto> players;
};

struct MatchInfoDto {
  std::string code;
  std::string name;
  int players = 0;
};

enum class LobbyActionDto { Create, List, Join };

struct LobbyRequestDto {
  LobbyActionDto action = LobbyActionDto::List;

  // Atributos para Creacion de Partida
  std::string match_name;

  // Atributos para Unirse a partida
  std::string code;
  std::string player_name;
  PlayerOutfitDto player_outfit{};
};

struct MatchInfo {
  std::string code;
  std::string name;
  int players = 0;
};

enum class LobbyAction { Create, List, Join };

struct LobbyRequest {
  LobbyAction action = LobbyAction::List;
  std::string text;
};

#endif
