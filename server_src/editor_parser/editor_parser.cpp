#include "editor_parser.h"

#include <climits>
#include <cstdint>
#include <map>
#include <optional>
#include <stdexcept>
#include <utility>

#include "../game/sectors/cavern_sector.h"
#include "../game/sectors/farm_sector.h"
#include "../game/sectors/village_sector.h"

namespace {
const toml::table& requiredTable(const toml::table& route,
                                 const char* key) {
    const toml::table* table = route[key].as_table();
    if (table == nullptr)
        throw std::runtime_error(TEXTO_ERROR_CAMPO + std::string(key));
    return *table;
}

int requiredInteger(const toml::table& table, const char* key,
                    const std::string& zone) {
    std::optional<std::int64_t> value = table[key].value<std::int64_t>();
    if (!value || *value < 0 || *value > INT_MAX)
        throw std::runtime_error(TEXTO_ERROR_CAMPO + zone + "." + key);
    return static_cast<int>(*value);
}

const toml::array& requiredArray(const toml::table& table, const char* key,
                                 const std::string& zone) {
    const toml::array* array = table[key].as_array();
    if (array == nullptr)
        throw std::runtime_error(TEXTO_ERROR_CAMPO + zone + "." + key);
    return *array;
}

Building makeBuilding(BuildingType type, Position topLeft, size_t width,
                      size_t height, IdSector interior = IdSector::VILLAGE,
                      int ownerId = INVALID_PLAYER_ID) {
    return Building{type,
                    topLeft,
                    width,
                    height,
                    Position(topLeft.x + width / 2, topLeft.y + height - 1),
                    interior,
                    ownerId};
}

CavernLevelConfig cavernConfig(size_t level) {
    std::vector<MineralTypes> minerals = {
        MineralTypes::COAL, MineralTypes::IRON, MineralTypes::LAPIZLAZULI};
    if (level >= 4)
        minerals.push_back(MineralTypes::GOLD);
    return CavernLevelConfig{
        .minMinerals = 8 + level * 2,
        .maxMinerals = 12 + level * 2,
        .minEnemyGroups = 3 + level,
        .maxEnemyGroups = 6 + level,
        .availableMinerals = std::move(minerals),
        .availableEnemies = {
            {EnemyType::SKELETON, SKELETON_GROUP, SKELETON_GROUP, SKELETON_MAX_LEVEL_COUNT},
            {EnemyType::ORC, ORC_MIN_GROUP, ORC_MAX_GROUP, ORC_MAX_LEVEL_COUNT},
            {EnemyType::VAMPIRE_MALE, VAMPIRE_GROUP, VAMPIRE_GROUP, VAMPIRE_MAX_LEVEL_COUNT},
            {EnemyType::SKULL_BLUE, SKULL_GROUP, SKULL_GROUP, SKULL_MAX_LEVEL_COUNT},
            {EnemyType::SKULL_GREEN, SKULL_GROUP, SKULL_GROUP, SKULL_MAX_LEVEL_COUNT},
        }};
}

} // namespace

std::vector<EditorParser::Object> EditorParser::readObjects(
    const toml::table& table, const std::string& zone, size_t width,
    size_t height) {
    std::vector<Object> result;
    std::map<Position, std::string> occupied;
    const toml::array& array = requiredArray(table, CLAVE_OBJETOS, zone);
    for (const toml::node& node : array) {
        const toml::table* object = node.as_table();
        if (object == nullptr)
            throw std::runtime_error(TEXTO_ERROR_CAMPO + zone + "." +
                                     CLAVE_OBJETOS);
        std::optional<std::string> type =
            (*object)[CLAVE_TIPO].value<std::string>();
        if (!type)
            throw std::runtime_error(TEXTO_ERROR_CAMPO + zone + "." +
                                     CLAVE_TIPO);
        int x = requiredInteger(*object, CLAVE_X, zone);
        int y = requiredInteger(*object, CLAVE_Y, zone);
        Position position(x, y);
        if (x >= static_cast<int>(width) || y >= static_cast<int>(height))
            throw std::runtime_error(TEXTO_ERROR_RANGO + zone + "." +
                                     *type);
        if (!occupied.emplace(position, *type).second)
            throw std::runtime_error(TEXTO_ERROR_OBJETO + zone);
        result.push_back({*type, position});
    }
    return result;
}

Position EditorParser::uniqueObject(const std::vector<Object>& objects,
                                    const std::string& type,
                                    const std::string& zone) {
    const Object* found = nullptr;
    for (const auto& object : objects)
        if (object.type == type) {
            found = &object;
            break;
        }
    if (found == nullptr)
        throw std::runtime_error(TEXTO_ERROR_CAMPO + zone + "." + type);
    for (const auto& object : objects)
        if (object.type == type && !(object.position == found->position))
            throw std::runtime_error(TEXTO_ERROR_OBJETO + zone + "." + type);
    return found->position;
}

std::map<Position, TerrainDecoration> EditorParser::farmDecorations(
    const std::vector<Object>& objects) {
    const std::map<std::string, TerrainDecoration> types = {
        {"Arbol1", Tree1},       {"Arbol2", Tree2},
        {"Piedra", Stone},       {"Agua", WaterDeco},
        {"ArbustoRedondo", TreeRounded}, {"ArbustoGrande", TreeBig},
        {"PiedraGrisGrande", StoneGrayBig}, {"PiedraGris", StoneGray},
        {"TroncoCaido", Log},    {"Tocon", Stump},
        {"BuzonRojo", MailboxRed}, {"CartelVacio", BlankSign}};
    std::map<Position, TerrainDecoration> result;
    for (const auto& object : objects) {
        auto it = types.find(object.type);
        if (it != types.end())
            result.emplace(object.position, it->second);
    }
    return result;
}

std::map<Position, TerrainDecoration> EditorParser::villageDecorations(
    const std::vector<Object>& objects) {
    const std::map<std::string, TerrainDecoration> types = {
        {"FarolNaranja", LanternOrange}, {"FarolAzul", LanternBlue},
        {"BancoMadera", Bench},         {"BuzonGris", MailBoxGray},
        {"BuzonAzul", MailboxBlue}};
    std::map<Position, TerrainDecoration> result;
    for (const auto& object : objects) {
        auto it = types.find(object.type);
        if (it != types.end())
            result.emplace(object.position, it->second);
    }
    return result;
}

std::map<Position, TerrainDecoration> EditorParser::cavernDecorations(
    const std::vector<Object>& objects) {
    const std::map<std::string, TerrainDecoration> types = {
        {"Barril", Barrel},       {"Calavera", SkullDeco},
        {"Hueso", Bone},          {"Escombros", Ruins},
        {"Antorcha", Torch},      {"Candelabro", Candle},
        {"Escudo", Shield},       {"Pozo", Pit}};
    std::map<Position, TerrainDecoration> result;
    for (const auto& object : objects) {
        auto it = types.find(object.type);
        if (it != types.end())
            result.emplace(object.position, it->second);
    }
    return result;
}

std::vector<Building> EditorParser::farmBuildings(
    const std::vector<Object>& objects) {
    std::vector<Building> result;
    const std::map<std::string, BuildingType> types = {
        {"Cabania1", BuildingType::CABIN_PLAYER_1},
        {"Cabania2", BuildingType::CABIN_PLAYER_2},
        {"Cabania3", BuildingType::CABIN_PLAYER_3},
        {"Cabania4", BuildingType::CABIN_PLAYER_4},
        {"Cabania5", BuildingType::CABIN_PLAYER_5}};
    for (const auto& object : objects) {
        auto it = types.find(object.type);
        if (it != types.end())
            result.push_back(makeBuilding(it->second, object.position, 3, 4,
                                          IdSector::FARM));
    }
    return result;
}

std::vector<Building> EditorParser::villageBuildings(
    const std::vector<Object>& objects) {
    std::vector<Building> result;
    const std::map<std::string, BuildingType> types = {
        {"CasaMarnie", BuildingType::SHOP_MARNIE},
        {"CasaClint", BuildingType::SHOP_CLINT},
        {"CasaPierre", BuildingType::SHOP_PIERRE},
        {"CasaRobin", BuildingType::SHOP_ROBIN},
        {"CentroComunitario", BuildingType::COMUNITARY_CENTRE}};
    for (const auto& object : objects) {
        auto it = types.find(object.type);
        if (it == types.end())
            continue;
        size_t width = object.type == "CentroComunitario" ? 8 : 5;
        size_t height = object.type == "CentroComunitario" ? 6 : 4;
        result.push_back(makeBuilding(it->second, object.position, width,
                                      height));
    }
    return result;
}

std::map<Position, MerchantType> EditorParser::villageMerchants(
    const std::vector<Object>& objects) {
    const std::map<std::string, MerchantType> types = {
        {"NpcPierre", MerchantType::PIERRE}, {"NpcClint", MerchantType::CLINT},
        {"NpcRobin", MerchantType::ROBIN},   {"NpcMarnie", MerchantType::MARNIE}};
    std::map<Position, MerchantType> result;
    for (const auto& object : objects) {
        auto it = types.find(object.type);
        if (it != types.end())
            result.emplace(object.position, it->second);
    }
    return result;
}

void EditorParser::parseFarm(World& world, const toml::table& route) const {
    const toml::table& table = requiredTable(route, CLAVE_GRANJA);
    size_t width = requiredInteger(table, CLAVE_ANCHO, CLAVE_GRANJA);
    size_t height = requiredInteger(table, CLAVE_ALTO, CLAVE_GRANJA);
    std::vector<Object> objects = readObjects(table, CLAVE_GRANJA, width, height);
    auto farm = std::make_unique<FarmSector>(
        width, height, farmDecorations(objects), farmBuildings(objects));
    world.addSector(std::move(farm));
}

void EditorParser::parseCavern(World& world, const toml::table& route)  const{
    const toml::table& table = requiredTable(route, CLAVE_CAVERNA);
    size_t width = requiredInteger(table, CLAVE_ANCHO, CLAVE_CAVERNA);
    size_t height = requiredInteger(table, CLAVE_ALTO, CLAVE_CAVERNA);
    const toml::array& levels = requiredArray(table, CLAVE_NIVELES, CLAVE_CAVERNA);
    if (levels.size() != MAX_CAVERN_LEVELS)
        throw std::runtime_error(TEXTO_ERROR_NIVELES);

    std::vector<std::vector<Object>> levelObjects;
    for (size_t i = 0; i < levels.size(); ++i) {
        const toml::table* level = levels[i].as_table();
        if (level == nullptr)
            throw std::runtime_error(TEXTO_ERROR_CAMPO + std::string(CLAVE_CAVERNA));
        std::string zone = std::string(CLAVE_CAVERNA) + TEXTO_NIVEL_ARCHIVO +
                           std::to_string(i + PRIMER_NIVEL_CAVERNA);
        levelObjects.push_back(readObjects(*level, zone, width, height));
        world.addSector(std::make_unique<CavernSector>(
            width, height,
            static_cast<IdSector>(static_cast<int>(IdSector::CAVERN_LEVEL_1) +
                                  static_cast<int>(i)),
            cavernConfig(i), cavernDecorations(levelObjects.back())));
    }

    Position firstExit = uniqueObject(levelObjects[0], "SalidaCaverna",
                                      "caverna nivel 1");
    const toml::table& villageTable = requiredTable(route, CLAVE_PUEBLO);
    size_t villageWidth = requiredInteger(villageTable, CLAVE_ANCHO, CLAVE_PUEBLO);
    size_t villageHeight = requiredInteger(villageTable, CLAVE_ALTO, CLAVE_PUEBLO);
    Position mineEntry = uniqueObject(
        readObjects(villageTable, CLAVE_PUEBLO, villageWidth, villageHeight),
        "EntradaMina", CLAVE_PUEBLO);
    world.addDoor(IdSector::VILLAGE, IdSector::CAVERN_LEVEL_1, mineEntry,
                   firstExit, DoorType::CavernEntry, DoorType::CavernExit);

    for (size_t i = 0; i + 1 < levelObjects.size(); ++i) {
        Position well = uniqueObject(levelObjects[i], "Pozo", "caverna nivel");
        Position stairs = uniqueObject(levelObjects[i + 1], "Escalera",
                                       "caverna nivel");
        IdSector origin = static_cast<IdSector>(
            static_cast<int>(IdSector::CAVERN_LEVEL_1) + static_cast<int>(i));
        IdSector destination = static_cast<IdSector>(
            static_cast<int>(IdSector::CAVERN_LEVEL_1) + static_cast<int>(i + 1));
        world.addDoor(origin, destination, well, stairs, DoorType::CavernExit,
                      DoorType::Stairs);
    }
}

void EditorParser::parseVillage(World& world, const toml::table& route) const {
    const toml::table& table = requiredTable(route, CLAVE_PUEBLO);
    size_t width = requiredInteger(table, CLAVE_ANCHO, CLAVE_PUEBLO);
    size_t height = requiredInteger(table, CLAVE_ALTO, CLAVE_PUEBLO);
    std::vector<Object> objects = readObjects(table, CLAVE_PUEBLO, width, height);
    auto village = std::make_unique<VillageSector>(
        width, height, villageDecorations(objects), villageBuildings(objects));
    world.addSector(std::move(village));
    for (const auto& [position, type] : villageMerchants(objects))
        world.spawnMerchant(IdSector::VILLAGE, position, type);
    Position farmExit = uniqueObject(objects, "SalidaGranja", CLAVE_PUEBLO);
    const toml::table& farmTable = requiredTable(route, CLAVE_GRANJA);
    size_t farmWidth = requiredInteger(farmTable, CLAVE_ANCHO, CLAVE_GRANJA);
    size_t farmHeight = requiredInteger(farmTable, CLAVE_ALTO, CLAVE_GRANJA);
    Position villageExit = uniqueObject(
        readObjects(farmTable, CLAVE_GRANJA, farmWidth, farmHeight),
        "SalidaPueblo", CLAVE_GRANJA);
    world.addDoor(IdSector::VILLAGE, IdSector::FARM, farmExit, villageExit,
                  DoorType::VillageEntry, DoorType::FarmExit);
}

World EditorParser::operator()() const {
    toml::table route;
    try {
        route = toml::parse_file(fileRoute);
    } catch (const toml::parse_error &error) {
        throw std::runtime_error("Error " + fileRoute + "\n" +
                                std::string(error.description()));
    }

    std::optional<std::string> name = route[CLAVE_NOMBRE].value<std::string>();
    if (!name)
        throw std::runtime_error(TEXTO_ERROR_CAMPO + std::string(CLAVE_NOMBRE));
    std::optional<std::int64_t> version = route[CLAVE_VERSION].value<std::int64_t>();
    if (!version || *version != VERSION_ARCHIVO_MAPA)
        throw std::runtime_error(TEXTO_ERROR_VERSION);

    World world(*name, this->code);
    parseFarm(world, route);
    parseVillage(world, route);
    parseCavern(world, route);

    return world;
}