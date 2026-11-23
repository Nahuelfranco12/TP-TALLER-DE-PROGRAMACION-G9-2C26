#include "merchants_factory.h"

#include "../inventory/chicken_egg.h"
#include "../inventory/cow_milk.h"
#include "../inventory/crop_item.h"
#include "../inventory/seed.h"
#include "../inventory/mineral_item.h"
#include "../inventory/animal_item.h"
#include "../inventory/chest_item.h"

std::unique_ptr<Merchant> MerchantsFactory::create(MerchantType type,
                                                   Position position) const {
  switch (type) {
  case MerchantType::PIERRE: {
    auto pierre = std::make_unique<Merchant>(position, type, "Pierre", "Hola! Soy Pierre. Vendo semillas y compro lo que produzca tu granja.");

    pierre->addSale("semilla_frutilla", PRICE_SEED, std::make_unique<Seed>(PRICE_SEED, CropTypes::STRAWBERRY));
    pierre->addSale("semilla_cebolla", PRICE_SEED, std::make_unique<Seed>(PRICE_SEED, CropTypes::GREEN_ONION));
    pierre->addSale("semilla_papa", PRICE_SEED, std::make_unique<Seed>(PRICE_SEED, CropTypes::POTATO));
    pierre->addSale("semilla_calabaza", PRICE_SEED, std::make_unique<Seed>(PRICE_SEED, CropTypes::PUMPKIN));

    pierre->addPurchase("frutilla", PRICE_STRAWBERRY, std::make_unique<CropItem>(PRICE_STRAWBERRY, CropTypes::STRAWBERRY, CropQuality::BASE));
    pierre->addPurchase("cebolla", PRICE_GREEN_ONION, std::make_unique<CropItem>(PRICE_GREEN_ONION, CropTypes::GREEN_ONION, CropQuality::BASE));
    pierre->addPurchase("papa", PRICE_POTATO, std::make_unique<CropItem>( PRICE_POTATO, CropTypes::POTATO, CropQuality::BASE));
    pierre->addPurchase("calabaza", PRICE_PUMPKIN, std::make_unique<CropItem>(PRICE_PUMPKIN, CropTypes::PUMPKIN, CropQuality::BASE));
    pierre->addPurchase("huevo", PRICE_EGG, std::make_unique<ChickenEgg>(PRICE_EGG));
    pierre->addPurchase("leche", PRICE_MILK, std::make_unique<CowMilk>(PRICE_MILK));
    return pierre;
  }
  case MerchantType::CLINT: {
    auto clint = std::make_unique<Merchant>(position, type, "Clint", "Soy Clint, el herrero. Te compro los minerales de la caverna.");

    clint->addPurchase("oro", PRICE_GOLD, std::make_unique<MineralItem>(PRICE_GOLD, MineralTypes::GOLD));
    clint->addPurchase("hierro", PRICE_IRON, std::make_unique<MineralItem>(PRICE_IRON, MineralTypes::IRON));
    clint->addPurchase("lapislazuli", PRICE_LAPIZLAZULI, std::make_unique<MineralItem>( PRICE_LAPIZLAZULI, MineralTypes::LAPIZLAZULI));
    clint->addPurchase("carbon", PRICE_COAL, std::make_unique<MineralItem>(PRICE_COAL, MineralTypes::COAL));
    return clint;
  }
  case MerchantType::ROBIN:
    return std::make_unique<Merchant>(position, type, "Robin", "Hola! Soy Robin. Hago decoraciones y cofres para tu granja.");
    robin->addSale("cofre", PRICE_CHEST, std::make_unique<ChestItem>());
    return robin;
  case MerchantType::MARNIE: {
    auto marnie = std::make_unique<Merchant>(position, type, "Marnie", "Hola, soy Marnie! Compro y vendo animales de granja.");
    marnie->addSale("vaca", PRICE_COW, std::make_unique<AnimalItem>(PRICE_COW, AnimalType::COW));
    marnie->addSale("gallina", PRICE_CHICKEN, std::make_unique<AnimalItem>(PRICE_CHICKEN,  AnimalType::CHICKEN));
    marnie->addPurchase("vaca", PRICE_COW, std::make_unique<AnimalItem>(PRICE_COW, AnimalType::COW));
    marnie->addPurchase("gallina", PRICE_CHICKEN, std::make_unique<AnimalItem>(PRICE_CHICKEN, AnimalType::CHICKEN));
    return marnie;
  }
  return nullptr;
}
}