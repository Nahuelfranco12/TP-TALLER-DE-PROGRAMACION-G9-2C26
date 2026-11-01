#ifndef MINERAL_ITEM_H_
#define MINERAL_ITEM_H_

#include "../game_constants.h"
#include "item.h"

class MineralItem : public Item {
private:
    MineralTypes mineralType;

public:
    MineralItem(double price, MineralTypes mineralType) : Item(price, ItemType::MINERAL), mineralType(mineralType) {}

    MineralTypes getMineralType() const { return mineralType; }

    bool stacksWith(const Item& other) const override;
};

#endif // MINERAL_ITEM_H_
