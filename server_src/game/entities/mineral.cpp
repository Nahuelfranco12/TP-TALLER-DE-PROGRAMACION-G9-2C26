#include "mineral.h"

#include "../game_constants.h"
#include "../inventory/item.h"
#include "../inventory/mineral_item.h"

std::unique_ptr<Item> Mineral::toItem() const {
    double price = 0;
    switch (this->type) {
        case MineralTypes::GOLD:
            price = PRICE_GOLD;
            break;
        case MineralTypes::IRON:
            price = PRICE_IRON;
            break;
        case MineralTypes::LAPIZLAZULI:
            price = PRICE_LAPIZLAZULI;
            break;
        case MineralTypes::COAL:
            price = PRICE_COAL;
            break;
    }
    return std::make_unique<MineralItem>(price, this->type);
}

void Mineral::pickaxeEffect() {
    // TODO: implementar (spawn de enemigos, perder el material)
}

EntityState Mineral::entityState() const override {
    EntityState state = Entity::entityState();
    state.mineralType = this->mineralType;
    return state;
}