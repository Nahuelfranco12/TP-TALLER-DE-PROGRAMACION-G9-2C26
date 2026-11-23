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
    case CropTypes::STRAWBERRY:
      return ItemTypeDto::SEED_STRAWBERRY;
    case CropTypes::GREEN_ONION:
      return ItemTypeDto::SEED_GREEN_ONION;
    case CropTypes::POTATO:
      return ItemTypeDto::SEED_POTATO;
    case CropTypes::PUMPKIN:
      return ItemTypeDto::SEED_PUMPKIN;
    }
    break;
  case ItemType::CROP:
    switch (static_cast<CropTypes>(item.subtype)) {
    case CropTypes::STRAWBERRY:
      return ItemTypeDto::CROP_STRAWBERRY;
    case CropTypes::GREEN_ONION:
      return ItemTypeDto::CROP_GREEN_ONION;
    case CropTypes::POTATO:
      return ItemTypeDto::CROP_POTATO;
    case CropTypes::PUMPKIN:
      return ItemTypeDto::CROP_PUMPKIN;
    }
    break;
  case ItemType::ANIMAL_PRODUCT:
    if (static_cast<AnimalType>(item.subtype) == AnimalType::COW)
      return ItemTypeDto::COW_MILK;
    return ItemTypeDto::CHICKEN_EGG;
  case ItemType::ANIMAL:
    if (static_cast<AnimalType>(item.subtype) == AnimalType::COW)
      return ItemTypeDto::ANIMAL_COW;
    return ItemTypeDto::ANIMAL_CHICKEN;
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
  case EntityTypes::ENEMY:
    switch (e.enemy.type) {
    case EnemyType::SKELETON:
      return EntityTypeDto::SKELETON;
    case EnemyType::ORC:
      return EntityTypeDto::ORC;
    case EnemyType::VAMPIRE_MALE:
      return EntityTypeDto::VAMPIRE_MALE;
    case EnemyType::VAMPIRE_FEMALE:
      return EntityTypeDto::VAMPIRE_FEMALE;
    case EnemyType::TRAP_FLAME:
      return EntityTypeDto::TRAP_FLAME;
    case EnemyType::TRAP_PINCH:
      return EntityTypeDto::TRAP_PINCH;
    case EnemyType::SKULL_BLUE:
      return EntityTypeDto::SKULL_BLUE;
    case EnemyType::SKULL_GREEN:
      return EntityTypeDto::SKULL_GREEN;    }
    break;
  case EntityTypes::BED:
      return EntityTypeDto::BED;
  case EntityTypes::NPC:
    switch (e.merchant.type) {
    case MerchantType::PIERRE:
      return EntityTypeDto::NPC_PIERRE;
    case MerchantType::CLINT:
      return EntityTypeDto::NPC_CLINT;
    case MerchantType::ROBIN:
      return EntityTypeDto::NPC_ROBIN;
    case MerchantType::MARNIE:
      return EntityTypeDto::NPC_MARNIE;
    }
    break;
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
  case CABIN_PLAYER_1:
  case CABIN_PLAYER_2:
  case CABIN_PLAYER_3:
  case CABIN_PLAYER_4:
  case CABIN_PLAYER_5:
    return SectorTypeDto::CABIN;
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

BuildingTypeDto GameDtosBuilder::toDto(BuildingType type) {
  switch (type) {
  case BuildingType::CABIN_PLAYER_1:
    return BuildingTypeDto::CABIN_PLAYER_1;
  case BuildingType::CABIN_PLAYER_2:
    return BuildingTypeDto::CABIN_PLAYER_2;
  case BuildingType::CABIN_PLAYER_3:
    return BuildingTypeDto::CABIN_PLAYER_3;
  case BuildingType::CABIN_PLAYER_4:
    return BuildingTypeDto::CABIN_PLAYER_4;
  case BuildingType::CABIN_PLAYER_5:
    return BuildingTypeDto::CABIN_PLAYER_5;
  case BuildingType::SHOP_MARNIE:
    return BuildingTypeDto::SHOP_MARNIE;
  case BuildingType::SHOP_CLINT:
    return BuildingTypeDto::SHOP_CLINT;
  case BuildingType::SHOP_PIERRE:
    return BuildingTypeDto::SHOP_PIERRE;
  case BuildingType::SHOP_ROBIN:
    return BuildingTypeDto::SHOP_ROBIN;
  case BuildingType::COMUNITARY_CENTRE:
    return BuildingTypeDto::COMUNITARY_CENTRE;
  }
  throw std::logic_error("BuildingType sin DTO");
}

SectorIdDto GameDtosBuilder::toDtoSectorId(IdSector id) {
  switch (id) {
  case IdSector::FARM:
    return SectorIdDto::FARM;
  case IdSector::VILLAGE:
    return SectorIdDto::VILLAGE;
  case IdSector::CAVERN_LEVEL_1:
    return SectorIdDto::CAVERN_LEVEL_1;
  case IdSector::CAVERN_LEVEL_2:
    return SectorIdDto::CAVERN_LEVEL_2;
  case IdSector::CAVERN_LEVEL_3:
    return SectorIdDto::CAVERN_LEVEL_3;
  case IdSector::CAVERN_LEVEL_4:
    return SectorIdDto::CAVERN_LEVEL_4;
  case IdSector::CAVERN_LEVEL_5:
    return SectorIdDto::CAVERN_LEVEL_5;
  case IdSector::CAVERN_LEVEL_6:
    return SectorIdDto::CAVERN_LEVEL_6;
  case IdSector::CAVERN_LEVEL_7:
    return SectorIdDto::CAVERN_LEVEL_7;
  case IdSector::CAVERN_LEVEL_8:
    return SectorIdDto::CAVERN_LEVEL_8;
  case IdSector::CAVERN_LEVEL_9:
    return SectorIdDto::CAVERN_LEVEL_9;
  case IdSector::CAVERN_LEVEL_10:
    return SectorIdDto::CAVERN_LEVEL_10;
  case IdSector::CABIN_PLAYER_1:
    return SectorIdDto::CABIN_PLAYER_1;
  case IdSector::CABIN_PLAYER_2:
    return SectorIdDto::CABIN_PLAYER_2;
  case IdSector::CABIN_PLAYER_3:
    return SectorIdDto::CABIN_PLAYER_3;
  case IdSector::CABIN_PLAYER_4:
    return SectorIdDto::CABIN_PLAYER_4;
  case IdSector::CABIN_PLAYER_5:
    return SectorIdDto::CABIN_PLAYER_5;
  }
  throw std::logic_error("Sector id sin DTO");
}

TerrainTypeDto GameDtosBuilder::toDto(TerrainType terrain) {
  switch (terrain) {
  case DIRT:
    return TerrainTypeDto::DIRT;
  case GRASS:
    return TerrainTypeDto::GRASS;
  case GROUND:
    return TerrainTypeDto::GROUND;
  case WOOD:
    return TerrainTypeDto::WOOD;
  case HOUSE:
    return TerrainTypeDto::HOUSE;
  }
  throw std::logic_error("TerrainType sin DTO");
}

TerrainDecorationDto GameDtosBuilder::toDto(TerrainDecoration decoration) {
  switch (decoration) {
  case NONE: return NoneDto;
  case Tree1: return Tree1Dto;
  case Tree2: return Tree2Dto;
  case Tree3: return Tree3Dto;
  case TreeRounded: return TreeRoundedDto;
  case TreeBig: return TreeBigDto;
  case Log: return LogDto;
  case Stump: return StumpDto;
  case Stone: return StoneDto;
  case StoneGray: return StoneGrayDto;
  case StoneGrayBig: return StoneGrayBigDto;
  case WaterDeco: return WaterDecoDto;
  case MailboxRed: return MailboxRedDto;
  case MailboxBlue: return MailboxBlueDto;
  case MailBoxGray: return MailBoxGrayDto;
  case BlankSign: return BlankSignDto;
  case Barrel: return BarrelDto;
  case SkullDeco: return SkullDecoDto;
  case Bone: return BoneDto;
  case Ruins: return RuinsDto;
  case Torch: return TorchDto;
  case Candle: return CandleDto;
  case Shield: return ShieldDto;
  case Pit: return PitDto;
  case LanternOrange: return LanternOrangeDto;
  case LanternBlue: return LanternBlueDto;
  case Bench: return BenchDto;
  }
  throw std::logic_error("TerrainDecoration sin DTO");
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
          sectorDto.sector[x][y] = {toDto(t.type), toDto(t.decoration),
                                    t.transitable, t.arable, t.isDoor,
                                    static_cast<DoorTypeDto>(t.doorType),
                                    t.tilled};
        }

      sectorDto.buildings.reserve(sectorState.buildings.size());
      for (const BuildingState &building : sectorState.buildings) {
        sectorDto.buildings.push_back(
            {toDto(building.type),
             {building.topLeft.x, building.topLeft.y},
             building.width,
             building.height,
             {building.door.x, building.door.y},
             toDtoSectorId(building.interior),
             building.ownerId});
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
                inv.slots.push_back({i.count, toDto(i),
                                     static_cast<CropQualityDto>(i.quality)});
              for (const ToolState &t : playerState.inventory.tools)
                inv.tools.push_back(toDto(t.type));
              playerDto.inventory.push_back(std::move(inv));
              playerDto.actualTool =
                  static_cast<ToolTypeDto>(playerState.actualTool);
              if (playerState.pendingGift.count > 0) {
                playerDto.pendingGift.giverId = playerState.pendingGiftGiverId;
                playerDto.pendingGift.gift = {
                    playerState.pendingGift.count,
                    toDto(playerState.pendingGift),
                    static_cast<CropQualityDto>(
                        playerState.pendingGift.quality)};
              }
            }
            sectorDto.players[pos] = std::move(playerDto);
          }
        } else if (auto type = toDto(e)) {
          EntityDto entityDto;
          entityDto.type = *type;
          entityDto.ready = e.animal.is_ready;

          // TODO: revisar
          entityDto.crop.type = static_cast<CropTypeDto>(e.crop.type);
          entityDto.crop.growth = static_cast<CropGrowthDto>(e.crop.growth);
          entityDto.crop.needsWater = e.crop.needsWater;

          entityDto.mineral.remainingHits = e.mineral.remainingHits;
          entityDto.enemy.alive = e.enemy.is_alive;
          entityDto.enemy.direction = e.enemy.direction;
          sectorDto.entities[pos] = entityDto;
        }
      }
    }
  }

  sectorDto.time = {state.time.hours, state.time.minutes};
  sectorDto.dayNumber = state.dayNumber;

  for (const ChatMessageState &message : state.chat) {
    bool forEveryone = message.toId == -1;
    bool forMe = message.toId == clientId;
    bool fromMe = message.fromId == clientId;
    if (forEveryone || forMe || fromMe) {
      sectorDto.chat.push_back({message.fromName, message.text, !forEveryone});
    }
  }

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
          sectorDto.sector[x][y] = {toDto(t.type), toDto(t.decoration),
                                    t.transitable, t.arable, t.isDoor,
                                    static_cast<DoorTypeDto>(t.doorType),
                                    t.tilled};
        }

      sectorDto.buildings.reserve(sectorState.buildings.size());
      for (const BuildingState &building : sectorState.buildings) {
        sectorDto.buildings.push_back(
            {toDto(building.type),
             {building.topLeft.x, building.topLeft.y},
             building.width,
             building.height,
             {building.door.x, building.door.y},
             toDtoSectorId(building.interior),
             building.ownerId});
      }
    }
  }

  return sectorDto;
}
