#ifndef CROP_H_
#define CROP_H_

#include "entity.h"
#include "collectable.h"
#include "../game_constants.h"

class Crop : public Entity, public ICollectable {
private:
    CropTypes type;
    CropGrowth growth;
    double progress;

public:
    Crop(Position position, CropTypes type) : Entity(position.x, position.y, EntityTypes::CROP), type(type), growth(CropGrowth::SEED_STAGE), progress(0) {};

    void tick() override {
        
    }
};

#endif // CROP_H_