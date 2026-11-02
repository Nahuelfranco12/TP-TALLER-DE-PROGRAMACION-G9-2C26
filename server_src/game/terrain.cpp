#include "terrain.h"

bool Terrain::isTransitable() const { return this->transitable; }
bool Terrain::isArable() const { return this->arable; }
TerrainType Terrain::getTerrainType() const { return this->terrainType; }
