#include "rotating_merchant.h"

void RotatingMerchant::refreshCatalog()  {
    for (Offer &offer : sales)
        stock.push_back(std::move(offer));
        
    sales.clear();

    while (sales.size() < dailyProducts && !stock.empty()) {
        size_t index = std::rand() % stock.size();
        sales.push_back(std::move(stock[index]));
        stock.erase(stock.begin() + index);
    }
}