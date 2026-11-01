#ifndef GAME_DTOS_BUILDER_H_
#define GAME_DTOS_BUILDER_H_

#include <optional>

#include "game_dtos.h"
#include "../server_src/world_state.h"

class GameDtosBuilder {
private:
    ItemTypeDto toDto(const ItemState& itemState);
    ToolTypeDto toDto(AvailableTools tool);
    std::optional<EntityTypeDto> toDto(const EntityState& entity);
    SectorTypeDto toDto(IdSector id);
    TerrainTypeDto toDto(TerrainType terrain);

public:
    std::optional<SectorStateDto> build(const WorldState& state, int clientId, const SectorMapState* map);
};

#endif // GAME_DTOS_BUILDER_H_