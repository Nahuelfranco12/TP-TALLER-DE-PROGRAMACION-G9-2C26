#ifndef WORLD_STATE_H_
#define WORLD_STATE_H_

#include "game_constants.h"
#include "terrain.h"
#include "position.h"

#include <vector>
#include <cstddef>
#include <cstdint>

struct TerrainState {
    TerrainType type;
    bool transitable;
    bool arable;
};

struct EntityState {
    EntityTypes type;
    Position position;
    int playerId; // INVALID_PLAYER_ID en caso de no ser jugador.
    MineralTypes mineralType; // en caso de ser mineral.
    AnimalType animalType; // en caso de ser animal.

    // TODO: cultivos y npcs
};

struct ItemState {
    ItemType type;
    uint8_t subtype; // MineralTypes casteado, 0 en caso contrario
    uint8_t count;
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
    int id;
    Position position;
    double life;
    double energy;
    size_t coins;
    IdSector sector;

    PlayerOutfitState outfit;

    InventoryState inventory;
};

struct SectorMapState {
    IdSector id;
    size_t width;
    size_t height;
    std::vector<std::vector<TerrainState>> tiles;
};

struct SectorState {
    IdSector id;
    size_t width;
    size_t height;
    std::vector<EntityState> entities;
};

struct WorldState {
    std::vector<SectorState> sectors;
    std::vector<PlayerState> players;
};

#endif // WORLD_STATE_H_
