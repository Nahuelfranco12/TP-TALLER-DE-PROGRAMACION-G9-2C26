#include "game_dtos_builder.h"

#include <map>
#include <stdexcept>

ItemTypeDto GameDtosBuilder::toDto(const ItemState& item) {
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
            return ItemTypeDto::SEED;
        case ItemType::CROP:
            return ItemTypeDto::CULTIVO;
        case ItemType::ANIMAL_PRODUCT:
            return ItemTypeDto::CHICKEN_EGG;   // TODO: huevo o leche
        default: break;
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

std::optional<EntityTypeDto> GameDtosBuilder::toDto(const EntityState& e) {
    switch (e.type) {
        case EntityTypes::MINERAL:
            switch (e.mineralType) {
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
            return e.animalType == AnimalType::COW ? EntityTypeDto::COW : EntityTypeDto::CHICKEN;
        default: break;
    }
    return std::nullopt;
}

SectorTypeDto GameDtosBuilder::toDto(IdSector id) {
    switch (id) {
        case FARM:
            return SectorTypeDto::FARM;
        case VILLAGE:
            return SectorTypeDto::VILLAGE;
        case CAVERN_LEVEL:
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
