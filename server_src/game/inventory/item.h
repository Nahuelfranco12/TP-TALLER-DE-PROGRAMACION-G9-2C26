#ifndef ITEM_H_
#define ITEM_H_

#include <variant>

#include "../game_constants.h"

using ItemSubtype = std::variant<AnimalType, MineralTypes>;

class Item {
private:
  double price;
  ItemType type;
  ItemSubtype subtype;

public:
  Item(double price, ItemType type, ItemSubtype subtype)
      : price(price), type(type), subtype(subtype) {}
  virtual ~Item() = default;

  double getPrice() const { return this->price; }
  ItemType getType() const { return this->type; }
  const ItemSubtype &getSubtype() const { return subtype; }

  virtual bool stacksWith(const Item &other) const {
    return this->type == other.getType();
  }

  int subtypeToInt() const {
    return std::visit([](auto e) { return static_cast<int>(e); },
                      this->subtype);
  }
};

#endif // ITEM_H_
