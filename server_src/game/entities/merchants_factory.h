#ifndef MERCHANTS_FACTORY_H_
#define MERCHANTS_FACTORY_H_

#include <memory>

#include "merchant.h"

class MerchantsFactory {
public:
  std::unique_ptr<Merchant> create(MerchantType type, Position position) const {
    switch (type) {
    case MerchantType::PIERRE:
      return std::make_unique<Merchant>(position, type, "Pierre", "Hola! Soy Pierre. Vendo semillas y compro lo que produzca tu granja.");
    case MerchantType::CLINT:
      return std::make_unique<Merchant>(position, type, "Clint", "Soy Clint, el herrero. Te compro los minerales de la caverna.");
    case MerchantType::ROBIN:
      return std::make_unique<Merchant>(position, type, "Robin", "Hola! Soy Robin. Hago decoraciones y cofres para tu granja.");
    case MerchantType::MARNIE:
      return std::make_unique<Merchant>(position, type, "Marnie", "Hola, soy Marnie! Compro y vendo animales de granja.");
    }
    return nullptr;
  }
};

#endif // MERCHANTS_FACTORY_H_