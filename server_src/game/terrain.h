#ifndef TERRAIN_H_
#define TERRAIN_H_

#include "game_constants.h"

class Terrain {
private:
  bool transitable;
  bool arable;
  bool tilled;
  TerrainType terrainType;

public:
  Terrain(bool transitable, bool arable, TerrainType type)
      : transitable(transitable), arable(arable), tilled(false), terrainType(type) {}

  bool isTransitable() const { return this->transitable; }
  bool isArable() const { return this->arable; }
  bool isTilled() const { return this->tilled; }
  TerrainType getTerrainType() const { return this->terrainType; }
  bool till() { 
    if(!this->arable || this->tilled) 
      return false;
    this->tilled = true;
    return true;
  }
};

#endif // TERRAIN_H_
