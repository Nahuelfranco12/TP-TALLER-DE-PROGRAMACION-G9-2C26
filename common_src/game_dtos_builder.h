#ifndef GAME_DTOS_BUILDER_H_
#define GAME_DTOS_BUILDER_H_

#include <optional>

#include "../server_src/world_state.h"
#include "game_dtos.h"

class GameDtosBuilder {
private:
  static ItemTypeDto toDto(const ItemState &itemState);
  static ToolTypeDto toDto(AvailableTools tool);
  static std::optional<EntityTypeDto> toDto(const EntityState &entity);
  static SectorTypeDto toDto(IdSector id);
  static TerrainTypeDto toDto(TerrainType terrain);

public:
  std::optional<SectorStateDto> build(const WorldState &state, int clientId);

  std::optional<SectorStateDto> buildSectorMap(const WorldState &state, SectorTypeDto sectorType);
};

#endif // GAME_DTOS_BUILDER_H_
