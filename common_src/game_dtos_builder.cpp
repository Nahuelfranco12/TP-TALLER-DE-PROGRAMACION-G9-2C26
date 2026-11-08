#include "game_dtos_builder.h"

#include <map>
#include <stdexcept>
#include <utility>
#include <vector>

ItemTypeDto GameDtosBuilder::toDto(const ItemState &item) {
  switch (item.type) {
  case ItemType::MINERAL:
    switch (static_cast<MineralTypes>(item.subtype)) {
    case MineralTypes::GOLD:
      return ItemTypeDto::MINERAL_GOLD;
    case MineralTypes::IRON:
      return ItemTypeDto::MINERAL_IRON;
    case MineralTypes::LAPIZLAZULI:
      return ItemTypeDto::MINERAL_LAPIZLAZULI;
    case MineralTypes::COAL:
      return ItemTypeDto::MINERAL_COAL;
    }
    break;
  case ItemType::SEED:
    switch (static_cast<CropTypes>(item.subtype)) {
        case CropTypes::STRAWBERRY:  return ItemTypeDto::SEED_STRAWBERRY;
        case CropTypes::GREEN_ONION: return ItemTypeDto::SEED_GREEN_ONION;
        case CropTypes::POTATO:      return ItemTypeDto::SEED_POTATO;
        case CropTypes::PUMPKIN:     return ItemTypeDto::SEED_PUMPKIN;
    }
    break;
  case ItemType::CROP:
      switch (static_cast<CropTypes>(item.subtype)) {
          case CropTypes::STRAWBERRY:  return ItemTypeDto::CROP_STRAWBERRY;
          case CropTypes::GREEN_ONION: return ItemTypeDto::CROP_GREEN_ONION;
          case CropTypes::POTATO:      return ItemTypeDto::CROP_POTATO;
          case CropTypes::PUMPKIN:     return ItemTypeDto::CROP_PUMPKIN;
      }
      break;
  case ItemType::ANIMAL_PRODUCT:
      if (static_cast<AnimalType>(item.subtype) == AnimalType::COW)
          return ItemTypeDto::COW_MILK;
      return ItemTypeDto::CHICKEN_EGG;
  default:
    break;
  }
  throw std::logic_error("ItemType sin DTO");
}

ToolTypeDto GameDtosBuilder::toDto(AvailableTools tool) {
  switch (tool) {
  case AvailableTools::SWORD:
    return ToolTypeDto::SWORD;
  case AvailableTools::PICKAXE:
    return ToolTypeDto::PICKAXE;
  case AvailableTools::SHOVEL:
    return ToolTypeDto::SHOVEL;
  case AvailableTools::WATERING_CAN:
    return ToolTypeDto::WATERING_CAN;
  }
  throw std::logic_error("AvailableTools sin DTO");
}

std::optional<EntityTypeDto> GameDtosBuilder::toDto(const EntityState &e) {
  switch (e.type) {
  case EntityTypes::MINERAL:
    switch (e.mineral.type) {
    case MineralTypes::GOLD:
      return EntityTypeDto::MINERAL_GOLD;
    case MineralTypes::IRON:
      return EntityTypeDto::MINERAL_IRON;
    case MineralTypes::LAPIZLAZULI:
      return EntityTypeDto::MINERAL_LAPIZLAZULI;
    case MineralTypes::COAL:
      return EntityTypeDto::MINERAL_COAL;
    }
    break;
  case EntityTypes::ANIMAL:
    return e.animal.type == AnimalType::COW ? EntityTypeDto::COW
                                           : EntityTypeDto::CHICKEN;
  case EntityTypes::CROP:
    return EntityTypeDto::CROP;
  default:
    break;
  }
  return std::nullopt;
}

SectorTypeDto GameDtosBuilder::toDto(IdSector id) {
  switch (id) {
  case FARM:
    return SectorTypeDto::FARM;
  case VILLAGE:
    return SectorTypeDto::VILLAGE;
  case IdSector::CAVERN_LEVEL_1:
  case IdSector::CAVERN_LEVEL_2:
  case IdSector::CAVERN_LEVEL_3:
  case IdSector::CAVERN_LEVEL_4:
  case IdSector::CAVERN_LEVEL_5:
  case IdSector::CAVERN_LEVEL_6:
  case IdSector::CAVERN_LEVEL_7:
  case IdSector::CAVERN_LEVEL_8:
  case IdSector::CAVERN_LEVEL_9:
  case IdSector::CAVERN_LEVEL_10:
      return SectorTypeDto::CAVERN;
  }
  throw std::logic_error("IdSector sin DTO");
}

TerrainTypeDto GameDtosBuilder::toDto(TerrainType terrain) {
  switch (terrain) {
  case DIRT:
    return TerrainTypeDto::DIRT;
  case GRASS:
    return TerrainTypeDto::GRASS;
  case GROUND:
    return TerrainTypeDto::GROUND;
  }
  throw std::logic_error("TerrainType sin DTO");
}

std::optional<SectorStateDto> GameDtosBuilder::build(const WorldState &state,
                                                     int clientId) {
  std::map<int, const PlayerState *> byId;
  for (const PlayerState &playerState : state.players)
    byId[playerState.id] = &playerState;

  auto actualPlayerIt = byId.find(clientId);
  if (actualPlayerIt == byId.end())
    return std::nullopt;
  const PlayerState &actualPlayer = *actualPlayerIt->second;

  SectorStateDto sectorDto;
  sectorDto.type = toDto(actualPlayer.sector);

  for (const SectorState &sectorState : state.sectors) {
    if (sectorState.id == actualPlayer.sector) {
      sectorDto.width = sectorState.width;
      sectorDto.height = sectorState.height;

      sectorDto.sector.assign(sectorDto.width,
                              std::vector<TileDto>(sectorDto.height));
      for (size_t x = 0; x < sectorDto.width; ++x)
        for (size_t y = 0; y < sectorDto.height; ++y) {
          const TerrainState &t = sectorState.tiles[x][y];
          sectorDto.sector[x][y] = {toDto(t.type), t.transitable, t.arable,
                                    t.isDoor};
        }

      for (const EntityState &e : sectorState.entities) {
        GamePositionDto pos{e.position.x, e.position.y};

        if (e.type == EntityTypes::PLAYER) {
          auto it = byId.find(e.playerId);
          if (it != byId.end()) {
            const PlayerState &playerState = *it->second;

            PlayerDto playerDto{};
            playerDto.id = playerState.id;

            playerDto.outfit.hat =
                static_cast<PlayerHatsDto>(playerState.outfit.hat);
            playerDto.outfit.hair =
                static_cast<PlayerHairsDto>(playerState.outfit.hairs);
            playerDto.outfit.tshirt =
                static_cast<PlayerTShirtsDto>(playerState.outfit.tshirt);
            playerDto.outfit.pants =
                static_cast<PlayerPantsDto>(playerState.outfit.pants);

            if (playerState.id == clientId) {
              playerDto.life = static_cast<uint8_t>(playerState.life);
              playerDto.energy = static_cast<uint8_t>(playerState.energy);
              playerDto.coins = static_cast<uint32_t>(playerState.coins);

              InventoryDto inv;
              inv.ownerId = playerState.id;
              for (const ItemState &i : playerState.inventory.items)
                inv.slots.push_back({i.count, toDto(i), static_cast<CropQualityDto>(i.quality)});
              for (const ToolState &t : playerState.inventory.tools)
                inv.tools.push_back(toDto(t.type));
              playerDto.inventory.push_back(std::move(inv));
              playerDto.actualTool =
                  static_cast<ToolTypeDto>(playerState.actualTool);
            }
            sectorDto.players[pos] = std::move(playerDto);
          }
        } else if (auto type = toDto(e)) {
          EntityDto entityDto;
          entityDto.type = *type;
          entityDto.ready = e.animal.is_ready;
          entityDto.crop.type = static_cast<CropTypeDto>(e.crop.type);
          entityDto.crop.growth = static_cast<CropGrowthDto>(e.crop.growth);
          sectorDto.entities[pos] = entityDto;
        }
      }
    }
  }

  sectorDto.time = {state.time.hours, state.time.minutes};
  sectorDto.dayNumber = state.dayNumber;

  return sectorDto;
}

std::optional<SectorStateDto>
GameDtosBuilder::buildSectorMap(const WorldState &state,
                                SectorTypeDto sectorType) {
  SectorStateDto sectorDto;
  sectorDto.type = sectorType;

  for (const SectorState &sectorState : state.sectors) {
    if (sectorState.id == static_cast<IdSector>(sectorType)) {
      sectorDto.width = sectorState.width;
      sectorDto.height = sectorState.height;

      sectorDto.sector.assign(sectorDto.width,
                              std::vector<TileDto>(sectorDto.height));
      for (size_t x = 0; x < sectorDto.width; ++x)
        for (size_t y = 0; y < sectorDto.height; ++y) {
          const TerrainState &t = sectorState.tiles[x][y];
          sectorDto.sector[x][y] = {toDto(t.type), t.transitable, t.arable,
                                    t.isDoor};
        }
    }
  }

  return sectorDto;
}
