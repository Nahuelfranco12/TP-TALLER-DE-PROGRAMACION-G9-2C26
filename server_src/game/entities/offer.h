#ifndef OFFER_H_
#define OFFER_H_

#include <memory>
#include <string>

#include "../inventory/item.h"

struct Offer {
  std::string name;
  int price;
  std::unique_ptr<Item> sample;
};

#endif // OFFER_H_  