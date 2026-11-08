#ifndef TERRAIN_H_
#define TERRAIN_H_

#include "game_constants.h"

class Terrain {
private:
  bool transitable;
  bool arable;
  TerrainType terrainType;

public:
  Terrain(bool transitable, bool arable, TerrainType type)
      : transitable(transitable), arable(arable), terrainType(type) {}

  bool isTransitable() const { return this->transitable; }
  bool isArable() const { return this->arable; }
  TerrainType getTerrainType() const { return this->terrainType; }
};

#endif // TERRAIN_H_
