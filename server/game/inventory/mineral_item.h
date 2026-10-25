#ifndef MINERAL_ITEM_H_
#define MINERAL_ITEM_H_

#include "item.h"

class MineralItem : public Item {
private:
public:
    MineralItem(double price) : Item(price) {};
};

#endif MINERAL_ITEM_H_
