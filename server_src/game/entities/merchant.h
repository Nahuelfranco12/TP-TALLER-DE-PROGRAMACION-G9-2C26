#ifndef MERCHANT_H_
#define MERCHANT_H_

#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "entity.h"
#include "interactable.h"
#include "offer.h"

class Merchant : public Entity, public Interactable {
private:
    MerchantType merchantType;
    std::string name;
    std::string greeting;
    std::vector<Offer> sales;
    std::vector<Offer> purchases;

    const Offer *find(const std::vector<Offer> &offers, const std::string &productName) const;

public:
    Merchant(Position position, MerchantType merchantType, const std::string &name, const std::string &greeting);

    void addSale(const std::string &productName, int price, std::unique_ptr<Item> sample);
    void addPurchase(const std::string &productName, int price, std::unique_ptr<Item> sample);

    const Offer *findSale(const std::string &productName) const;
    const Offer *findPurchase(const std::string &productName) const;

    const std::string &getName() const;
    const std::vector<Offer> &getSales() const;
    const std::vector<Offer> &getPurchases() const ;

    EntityState entityState() const override;

    void interact(World &world, Player &player) override;
};

#endif // MERCHANT_H_