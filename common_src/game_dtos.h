#ifndef DTOS_H_
#define DTOS_H_

#include <list>
#include <string>

enum class DirectionDto { Up, Down, Left, Right};
enum class TerrainTypeDto { DIRT, GRASS, GROUND, DOOR }; // TODO: en principio puerta es parte del enum (por si se quiere mostrar distinto)
enum class SectorTypeDto { FARM, VILLAGE, CAVERN };

// TODO: revisar para que sea acorde a SDL
enum class PlayerHatsDto { COMMON_HAT, FARMER_HAT };
enum class PlayerHairsDto { BLONDE, BROWN };
enum class PlayerTShirtsDto { BLACK, WHITE };
enum class PlayerPantsDto { JEANS, SHORTS, SKIRT };

enum class ItemTypeDto {
    MINERAL_GOLD,
    MINERAL_IRON,
    MINERAL_LAPIZLAZULI,
    MINERAL_COAL,
    MINERAL_SEED,
    CHICKEN_EGG,
    COW_MILK,
    CULTIVO, // TODO: los distintos tipo de cultivos + su rareza
};

enum class EntityTypeDto {
    COW,
    CHICKEN,
    SKELETON,
    
    // TODO: resto de enemigos
    // TODO: NPCs del pueblo
};

struct MoveDto {
    DirectionDto direction = DirectionDto::Up;
};

struct MineDto {
    // TODO
};

struct PlayerPositionDto {
    int id = 0;
    int x = 0;
    int y = 0;
};

struct GamePositionDto {
    size_t x = 0;
    size_t y = 0;
};

struct TileDto {
    bool transitable;
    bool arable;
    TerrainType type;
};

struct PlayerDto {
    size_t id;

    PlayerHatsDto hat;
    PlayerHairsDto hair;
    PlayerTShirtsDto tshirt;
    PlayerPantsDto pants;

    std::map<int, InventoryDto> inventories;
};

struct InventorySlotDto {
    size_t count;
    ItemType item;
};

struct InventoryDto {
    size_t ownerId;

    std::list<InventorySlotDto> slots;
};

struct SectorStateDto {
    size_t width;
    size_t height;
    SectorTypeDto type;

    std::list<std::list<TileDto>> sector;
    std::map<GamePositionDto, PlayerDto> players;
    std::map<GamePositionDto, EntityTypeDto> entities;
};

// TODO: revisar para cuando se necesita mostrar el mapa completo
struct WorldStateDto {
    std::list<SectorState> world;
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
    std::string text;
};

#endif