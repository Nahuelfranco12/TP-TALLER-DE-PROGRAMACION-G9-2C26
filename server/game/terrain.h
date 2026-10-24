#ifndef TERRAIN_H_
#define TERRAIN_H_

enum TerrainType { DIRT, GRASS, GROUND };

class Terrain {
private:
    bool transitable;
    bool arable;
    TerrainType terrainType;

public:
    bool isTransitable();
    bool esArable();
    TerrainType getTerrainType();
};

#endif // TERRAIN_H_