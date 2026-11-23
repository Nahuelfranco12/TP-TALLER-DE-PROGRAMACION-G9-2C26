#ifndef ITEM_H_
#define ITEM_H_

#include <variant>
#include <memory>

#include "../game_constants.h"

using ItemSubtype = std::variant<AnimalType, MineralTypes, CropTypes, FurnitureType>;

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
  virtual double priceMultiplier() const {return 1.0;} 
  ItemType getType() const { return this->type; }
  const ItemSubtype &getSubtype() const { return subtype; }

  virtual bool stacksWith(const Item &other) const {
    return isSameProduct(other);
  }

  int subtypeToInt() const {
    return std::visit([](auto e) { return static_cast<int>(e); },
                      this->subtype);
  }

  bool isSameProduct(const Item &other) const {
    return getType() == other.getType() && subtypeToInt() == other.subtypeToInt();
  } 
};

#endif // ITEM_H_
