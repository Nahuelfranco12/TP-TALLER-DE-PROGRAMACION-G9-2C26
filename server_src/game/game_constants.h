#ifndef GAME_CONSTANTS_H_
#define GAME_CONSTANTS_H_

#define MAX_INVENTORY_ITEMS 9
#define MAX_INVETORY_STACK 50
#define MAX_INVENTORY_TOOLS 4

#define PRICE_GOLD 80
#define PRICE_IRON 50
#define PRICE_LAPIZLAZULI 40
#define PRICE_COAL 10

#define INVALID_PLAYER_ID -1

enum IdSector { FARM, VILLAGE, CAVERN_LEVEL };

enum class AnimalType { COW, CHICKEN };

enum class ItemType {
    MINERAL,
    SEED,
    DECORATION_PRODUCT,
    CROP,
    ANIMAL_PRODUCT
};

enum class AvailableTools { SWORD, PICKAXE, SHOVEL, WATERING_CAN };

enum class MineralTypes { GOLD, IRON, LAPIZLAZULI, COAL };
enum class MineralPickaxeTime { LOW, MEDIUM, HIGH, VERY_HIGH  };

enum class EntityTypes { PLAYER, ANIMAL, MINERAL, ENEMY, NPC };

// enum class CrowTypes {  }; // TODO: tipos de cultivo

#endif // GAME_CONSTANTS_H_