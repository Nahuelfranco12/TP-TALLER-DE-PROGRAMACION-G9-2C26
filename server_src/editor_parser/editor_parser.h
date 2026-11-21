#ifndef EDITOR_PARSER_H_
#define EDITOR_PARSER_H_

#include <string>
#include <vector>
#include <toml++/toml.hpp>
#include "../../editor/mapa/constantes_mapa.h"
#include "../game/world.h"

class EditorParser {
private:
    struct Object {
        std::string type;
        Position position;
    };

    std::string fileRoute;
    std::string code;

    static std::vector<Object> readObjects(const toml::table& table,
                                           const std::string& zone,
                                           size_t width, size_t height);
    static Position uniqueObject(const std::vector<Object>& objects,
                                 const std::string& type,
                                 const std::string& zone);
    static std::map<Position, TerrainDecoration> farmDecorations(
        const std::vector<Object>& objects);
    static std::map<Position, TerrainDecoration> villageDecorations(
        const std::vector<Object>& objects);
    static std::map<Position, TerrainDecoration> cavernDecorations(
        const std::vector<Object>& objects);
    static std::vector<Building> farmBuildings(
        const std::vector<Object>& objects);
    static std::vector<Building> villageBuildings(
        const std::vector<Object>& objects);

    void parseFarm(World& world, const toml::table& route) const;
    void parseCavern(World& world, const toml::table& route) const;
    void parseVillage(World& world, const toml::table& route) const;

public:
    explicit EditorParser(const std::string& fileRoute, std::string code) : fileRoute(fileRoute), code(code) {}

    World operator()() const;
};

#endif // EDITOR_PARSER_H_