#ifndef TERRAIN_H_
#define TERRAIN_H_

enum TerrainType { DIRT, GRASS, GROUND };

class Terrain {
private:
    bool transitable;
    bool arable;
    TerrainType terrainType;

public:
    Terrain(bool transitable, bool arable, TerrainType type) : transitable(transitable), arable(arable), terrainType(type) {}

    bool isTransitable() const;
    bool isArable() const;
    TerrainType getTerrainType() const;
};

#endif // TERRAIN_H_
