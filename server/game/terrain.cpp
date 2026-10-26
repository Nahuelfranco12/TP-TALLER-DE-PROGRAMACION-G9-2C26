#include "terrain.h"

bool Terrain::isTransitable() { return this->transitable; }

bool Terrain::isArable() { return this->arable; }

TerrainType Terrain::getTerrainType() { return this->terrainType; }
