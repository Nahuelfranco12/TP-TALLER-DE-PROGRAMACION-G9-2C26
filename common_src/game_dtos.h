#ifndef DTOS_H_
#define DTOS_H_

#include <list>
#include <string>

enum class Direction { Up, Down, Left, Right};
enum class TerrainType { DIRT, GRASS, GROUND, DOOR }; // TODO: en principio puerta es parte del enum (por si se quiere mostrar distinto)
enum class SectorType { FARM, VILLAGE, CAVERN };

// TODO: revisar para que sea acorde a SDL
enum class PlayerHats { COMMON_HAT, FARMER_HAT };
enum class PlayerHairs { BLONDE, BROWN };
enum class PlayerTShirts { BLACK, WHITE };
enum class PlayerPants { JEANS, SHORTS, SKIRT };

enum class ItemType {
    MINERAL_GOLD,
    MINERAL_IRON,
    MINERAL_LAPIZLAZULI,
    MINERAL_COAL,
    MINERAL_SEED,
    CHICKEN_EGG,
    COW_MILK,
    CULTIVO, // TODO: los distintos tipo de cultivos + su rareza
};

enum class EntityType {
    COW,
    CHICKEN,
    SKELETON,
    
    // TODO: resto de enemigos
    // TODO: NPCs del pueblo
};

struct MoveDto {
    Direction direction = Direction::Up;
};

struct MineDto {
    // TODO
};

struct PlayerPosition {
    int id = 0;
    int x = 0;
    int y = 0;
};

struct GamePosition {
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

    PlayerHats hat;
    PlayerHairs hair;
    PlayerTShirts tshirt;
    PlayerPants pants;

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

struct SectorState {
    size_t width;
    size_t height;
    SectorType type;

    std::list<std::list<TileDto>> sector;
    std::map<GamePosition, PlayerDto> players;
    std::map<GamePosition, EntityType> entities;
};

// TODO: revisar para cuando se necesita mostrar el mapa completo
struct WorldState {
    std::list<SectorState> world;
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