#ifndef ITEM_H_
#define ITEM_H_

enum class ItemType {
    MINERAL,
    SEED,
    DECORATION_PRODUCT,
    CROP,
    ANIMAL_PRODUCT
};

class Item {
private:
    double price;
    ItemType type;

public:
    Item(double price, ItemType type) : price(price), type(type) {}
    virtual ~Item() = default;

    double getPrice() const;
    ItemType getType() const;

    virtual bool stacksWith(const Item& other) const {
        return this->type == other.getType();
    }
};

#endif // ITEM_H_
