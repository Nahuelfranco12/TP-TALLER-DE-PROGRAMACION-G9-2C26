#ifndef CROP_H_
#define CROP_H_

#include "entity.h"
#include "collectable.h"
#include "crop_item.h"
#include "../game_constants.h"

#define PROGRESS_TO_EARLY_GROWTH 33
#define PROGRESS_TO_MID_GROWTH  66
#define PROGRESS_TO_FULL_GROWTH 100

#define PERFECT_PROGRESS_LIMIT 110
#define INCREDIBLE_PROGRESS_LIMIT 125
#define EXCELENT_PROGRESS_LIMIT 150
#define GOOD_PROGRESS_LIMIT 200

class Crop : public Entity, public ICollectable {
private:
    CropTypes type;
    double progress;

public:
    Crop(Position position, CropTypes type) : Entity(position.x, position.y, EntityTypes::CROP), type(type), progress(0) {};

    CropGrowth growth() const {
        if(progress >= PROGRESS_TO_FULL_GROWTH) return CropGrowth::FULL_GROWTH;
        if(progress >= PROGRESS_TO_MID_GROWTH) return CropGrowth::MID_GROWTH;
        if(progress >= PROGRESS_TO_EARLY_GROWTH) return CropGrowth::EARLY_GROWTH;
        return CropGrowth::SEED_STAGE;
    }

    CropQuality quality() const {
        if(progress < PERFECT_PROGRESS_LIMIT) return CropQuality::PERFECT;
        if(progress < INCREDIBLE_PROGRESS_LIMIT) return CropQuality::INCREDIBLE;
        if(progress < EXCELENT_PROGRESS_LIMIT) return CropQuality::EXCELENT;
        if(progress < GOOD_PROGRESS_LIMIT) return CropQuality::GOOD;
        return CropQuality::BASE;
    }

    bool canCollect() const override {
        return progress >= PROGRESS_TO_FULL_GROWTH;
    }

    std::unique_ptr<Item> collect() override {
        if(!canCollect) return nullptr;
        return std::make_unique<CropItem>(type, quality());
    }
    void tick() override {
        progress += 1;
    }

    EntityState entityState() const override {
        EntityState state = Entity::entityState();
        state.cropType = type;
        state.is_ready = canCollect();
        return state;
    }
};

#endif // CROP_H_