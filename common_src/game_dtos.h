#ifndef DTOS_H_
#define DTOS_H_

#include <list>
#include <vector>
#include <map>
#include <string>
#include <cstddef>
#include <cstdint>

enum class DirectionDto { Up, Down, Left, Right};
enum class TerrainTypeDto { DIRT, GRASS, GROUND, DOOR }; // TODO: en principio puerta es parte del enum (por si se quiere mostrar distinto)
enum class SectorTypeDto { FARM, VILLAGE, CAVERN };

// TODO: revisar para que sea acorde a SDL
enum PlayerHatsDto { CAP_HAT, FARMER_HAT, LEAF_HAT, CHEF_HAT, CROWN_HAT, BOWTIE_HAT }; // 6
enum PlayerHairsDto { CURLY_HAIR, STRAIGHT_HAIR, STRAIGHT_SHORT_HAIR, CURLY_SHORT_HAIR, AFRO_HAIR, EMO_HAIR}; // 6
enum PlayerTShirtsDto { BLUE_SHIRT, WHITE_SHIRT, PINK_SHIRT, PURPLE_SHIRT, GREE_SHIRT }; // 5
enum PlayerPantsDto { JEANS_PANTS, SKIRT_PANTS, FARMER_PANTS, FARMER_SHORT_PANTS }; // 4

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
    CULTIVO, // TODO: los distintos tipo de cultivos + su rareza
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

    // TODO: resto de enemigos
    // TODO: NPCs del pueblo
};

struct MoveDto {
    DirectionDto direction = DirectionDto::Up;
};

struct MineDto {
    // TODO
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

    bool operator<(const GamePositionDto& o) const {
        return x != o.x ? x < o.x : y < o.y;
    }
};

struct TileDto {
    TerrainTypeDto type;
    bool transitable;
    bool arable;
};

struct InventorySlotDto {
    int count;
    ItemTypeDto item;
};

struct InventoryDto {
    size_t ownerId;

    std::list<InventorySlotDto> slots;
    std::list<ToolTypeDto> tools;
};

struct PlayerDto {
    size_t id;

    PlayerOutfitDto outfit;

    double life;
    double energy;
    size_t coins;

    std::list<InventoryDto> inventory;
};

struct SectorStateDto {
    SectorTypeDto type;
    size_t width;
    size_t height;

    std::vector<std::vector<TileDto>> sector;
    std::map<GamePositionDto, PlayerDto> players;
    std::map<GamePositionDto, EntityTypeDto> entities;
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
    PlayerOutfitDto player_outfit;
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