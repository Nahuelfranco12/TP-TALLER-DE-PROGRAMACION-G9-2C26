#include "crop.h"

#include <algorithm>
#include <random>

// Calidad = 1 - penalizaciones, multiplicado por la suerte.
// Cada penalizacion llega al maximo con 1 dia entero de demora.
#define WEIGHT_WATER_DELAY 0.6
#define WEIGHT_HARVEST_DELAY 0.4
#define LUCK_MIN 0.9
#define LUCK_MAX 1.1

#define SCORE_PERFECT 0.90
#define SCORE_INCREDIBLE 0.75
#define SCORE_EXCELENT 0.55
#define SCORE_GOOD 0.35

namespace {
double rollLuck() {
  static thread_local std::mt19937 rng{std::random_device{}()};
  return std::uniform_real_distribution<double>(LUCK_MIN, LUCK_MAX)(rng);
}

double delayPenalty(size_t ticks) {
  return std::min(1.0, static_cast<double>(ticks) / TICKS_PER_DAY);
}
} // namespace

Crop::Crop(Position position, CropTypes type)
    : Entity(position.x, position.y, EntityTypes::CROP), type(type),
      config(cropConfig(type)), extraHarvestsLeft(config.extraHarvests),
      luck(rollLuck()) {
  // Recien plantada
  sinceWatered = waterIntervalTicks();
}

bool Crop::needsWater() const {
  return !fullyGrown() && sinceWatered >= waterIntervalTicks();
}

bool Crop::water() {
  if (!needsWater())
    return false;
  sinceWatered = 0;
  return true;
}

void Crop::tick() {
  if (fullyGrown()) {
    readyTicks++;
    return;
  }

  sinceWatered++;
  if (needsWater())
    thirstyTicks++;

  size_t limit = waterIntervalTicks() * (1 + config.maxSkippedWaterings);
  if (sinceWatered < limit)
    growthTicks++;
}

CropQuality Crop::quality() const {
  double score = (1.0 - WEIGHT_WATER_DELAY * delayPenalty(thirstyTicks) -
                  WEIGHT_HARVEST_DELAY * delayPenalty(readyTicks)) *
                 luck;
  if (score >= SCORE_PERFECT)
    return CropQuality::PERFECT;
  if (score >= SCORE_INCREDIBLE)
    return CropQuality::INCREDIBLE;
  if (score >= SCORE_EXCELENT)
    return CropQuality::EXCELENT;
  if (score >= SCORE_GOOD)
    return CropQuality::GOOD;
  return CropQuality::BASE;
}

std::unique_ptr<Item> Crop::collect() {
  if (!canCollect())
    return nullptr;
  auto item = std::make_unique<CropItem>(price(), type, quality());

  if (extraHarvestsLeft > 0) {
    extraHarvestsLeft--;
    growthTicks = totalGrowthTicks() - TICKS_PER_DAY;
    sinceWatered = 0;
    thirstyTicks = 0;
    readyTicks = 0;
    luck = rollLuck();
  }
  return item;
}

CropGrowth Crop::growth() const {
  size_t progress = growthTicks * 100 / totalGrowthTicks();
  if (progress >= 100)
    return CropGrowth::FULL_GROWTH;
  if (progress >= 66)
    return CropGrowth::MID_GROWTH;
  if (progress >= 33)
    return CropGrowth::EARLY_GROWTH;
  return CropGrowth::SEED_STAGE;
}

double Crop::price() const {
  switch (this->type) {
  case CropTypes::STRAWBERRY:
    return PRICE_STRAWBERRY;
  case CropTypes::GREEN_ONION:
    return PRICE_GREEN_ONION;
  case CropTypes::POTATO:
    return PRICE_POTATO;
  case CropTypes::PUMPKIN:
    return PRICE_PUMPKIN;
  }
  return 0;
}

EntityState Crop::entityState() const {
  EntityState state = Entity::entityState();
  state.crop.type = type;
  state.crop.growth = growth();
  state.crop.needsWater = needsWater();
  return state;
}
