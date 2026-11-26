#include "ids_partida.h"

#include "constantes_persistencia.h"

const TablaIds<CropTypes> &tablaIds(CropTypes) {
  static const TablaIds<CropTypes> tabla = {
      {CropTypes::STRAWBERRY, ID_CULTIVO_FRUTILLA},
      {CropTypes::GREEN_ONION, ID_CULTIVO_CEBOLLA_DE_VERDEO},
      {CropTypes::POTATO, ID_CULTIVO_PAPA},
      {CropTypes::PUMPKIN, ID_CULTIVO_CALABAZA}};
  return tabla;
}

const TablaIds<CropQuality> &tablaIds(CropQuality) {
  static const TablaIds<CropQuality> tabla = {
      {CropQuality::BASE, ID_CALIDAD_BASE},
      {CropQuality::GOOD, ID_CALIDAD_BUENA},
      {CropQuality::EXCELENT, ID_CALIDAD_EXCELENTE},
      {CropQuality::INCREDIBLE, ID_CALIDAD_INCREIBLE},
      {CropQuality::PERFECT, ID_CALIDAD_PERFECTA}};
  return tabla;
}

const TablaIds<AnimalType> &tablaIds(AnimalType) {
  static const TablaIds<AnimalType> tabla = {
      {AnimalType::COW, ID_ITEM_VACA}, {AnimalType::CHICKEN, ID_ITEM_GALLINA}};
  return tabla;
}

const TablaIds<ClaveItem> &tablaIds(ClaveItem) {
  static const TablaIds<ClaveItem> tabla = {
      {{ItemType::MINERAL, MineralTypes::GOLD}, ID_MINERAL_ORO},
      {{ItemType::MINERAL, MineralTypes::IRON}, ID_MINERAL_PLATA},
      {{ItemType::MINERAL, MineralTypes::LAPIZLAZULI}, ID_MINERAL_LAPISLAZULI},
      {{ItemType::MINERAL, MineralTypes::COAL}, ID_MINERAL_CARBON},
      {{ItemType::SEED, CropTypes::STRAWBERRY}, ID_ITEM_SEMILLA_FRUTILLA},
      {{ItemType::SEED, CropTypes::GREEN_ONION},
       ID_ITEM_SEMILLA_CEBOLLA_DE_VERDEO},
      {{ItemType::SEED, CropTypes::POTATO}, ID_ITEM_SEMILLA_PAPA},
      {{ItemType::SEED, CropTypes::PUMPKIN}, ID_ITEM_SEMILLA_CALABAZA},
      {{ItemType::CROP, CropTypes::STRAWBERRY}, ID_CULTIVO_FRUTILLA},
      {{ItemType::CROP, CropTypes::GREEN_ONION}, ID_CULTIVO_CEBOLLA_DE_VERDEO},
      {{ItemType::CROP, CropTypes::POTATO}, ID_CULTIVO_PAPA},
      {{ItemType::CROP, CropTypes::PUMPKIN}, ID_CULTIVO_CALABAZA},
      {{ItemType::ANIMAL_PRODUCT, AnimalType::COW}, ID_ITEM_LECHE},
      {{ItemType::ANIMAL_PRODUCT, AnimalType::CHICKEN}, ID_ITEM_HUEVO},
      {{ItemType::ANIMAL, AnimalType::COW}, ID_ITEM_VACA},
      {{ItemType::ANIMAL, AnimalType::CHICKEN}, ID_ITEM_GALLINA},
      {{ItemType::FURNITURE, FurnitureType::CHEST}, ID_ITEM_COFRE}};
  return tabla;
}
