#ifndef ITEM_H_
#define ITEM_H_

class Item {
private:
    double price;

public:
    Item(double price) : price(price) {};

    // TODO: revisar TDA al momento de venderlo
    double getPrice();    
};

#endif // ITEM_H_