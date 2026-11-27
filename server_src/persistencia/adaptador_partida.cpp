#include "adaptador_partida.h"

#include <algorithm>
#include <cstddef>
#include <stdexcept>
#include <utility>
#include <vector>
#include <memory>
#include <variant>

#include "constantes_persistencia.h"
#include "../game/inventory/item_factory.h"
#include "ids_partida.h"
#include "../game/entities/chest.h"
#include "../game/cheatable/growth_cheat.h"
#include "server_src/persistencia/partida_guardada.h"

namespace {
ItemSubtype subtipoDe(const ItemState &item) {
  switch (item.type) {
  case ItemType::MINERAL:
    return static_cast<MineralTypes>(item.subtype);
  case ItemType::SEED:
  case ItemType::CROP:
    return static_cast<CropTypes>(item.subtype);
  case ItemType::ANIMAL_PRODUCT:
  case ItemType::ANIMAL:
    return static_cast<AnimalType>(item.subtype);
  case ItemType::FURNITURE:
    return static_cast<FurnitureType>(item.subtype);
  case ItemType::DECORATION_PRODUCT:
    break;
  }
  throw std::logic_error(ERROR_ADAPTADOR_ITEM_SIN_SUBTIPO);
}

bool esGuardable(const ItemState &item) {
  bool esCama = item.type == ItemType::FURNITURE && static_cast<FurnitureType>(item.subtype) == FurnitureType::BED;
  return item.type != ItemType::DECORATION_PRODUCT&& !esCama;
}

ItemGuardado itemGuardadoDe(const ItemState &item) {
  return ItemGuardado{item.type, subtipoDe(item), item.quality, item.count};
}

std::vector<ItemGuardado> itemsGuardablesDe(const InventoryState &inventario) {
  std::vector<ItemGuardado> items;
  for (const ItemState &item : inventario.items)
    if (esGuardable(item))
      items.push_back(itemGuardadoDe(item));
  return items;
}

OutfitGuardado outfitGuardadoDe(const PlayerOutfitState &outfit) {
  return OutfitGuardado{
      static_cast<int>(outfit.hat), static_cast<int>(outfit.hairs),
      static_cast<int>(outfit.tshirt), static_cast<int>(outfit.pants)};
}

JugadorGuardado jugadorGuardadoDe(const Player &jugador) {
  PlayerState estado = jugador.state();
  return JugadorGuardado{jugador.getName(),
                         //static_cast<std::size_t>(estado.id),
                         outfitGuardadoDe(estado.outfit),
                         estado.life,
                         estado.energy,
                         estado.coins,
                         itemsGuardablesDe(estado.inventory)};
}

void actualizarJugador(std::vector<JugadorGuardado> &jugadores,
                       JugadorGuardado jugador) {
  for (JugadorGuardado &guardado : jugadores) {
    if (guardado.nombre == jugador.nombre) {
      guardado = std::move(jugador);
      return;
    }
  }
  jugadores.push_back(std::move(jugador));
}

std::vector<CeldaGuardada> aradasDe(const Sector &granja) {
  std::vector<CeldaGuardada> aradas;
  for (std::size_t x = 0; x < granja.getWidth(); ++x)
    for (std::size_t y = 0; y < granja.getHeight(); ++y)
      if (granja.isTilled(Position(x, y)))
        aradas.push_back(CeldaGuardada{x, y});
  return aradas;
}

CultivoGuardado cultivoGuardadoDe(const EntityState &entidad) {
  const CropState &cultivo = entidad.crop;
  return CultivoGuardado{cultivo.type,
                         entidad.position.x,
                         entidad.position.y,
                         cultivo.growthTicks,
                         cultivo.sinceWatered,
                         cultivo.thirstyTicks,
                         cultivo.readyTicks,
                         cultivo.extraHarvestsLeft,
                         cultivo.luck};
}

bool esCofre(const EntityState &entidad) {
  return entidad.type == EntityTypes::FURNITURE &&
         entidad.furniture.type == FurnitureType::CHEST;
}

CofreGuardado cofreGuardadoDe(const EntityState &entidad) {
  return CofreGuardado{entidad.position.x, entidad.position.y,
                       itemsGuardablesDe(entidad.chest.inventory)};
}

std::vector<CofreGuardado> cofresDe(const WorldState &estado) {
  std::vector<CofreGuardado> cofres;
  for (const SectorState &sector : estado.sectors)
    if (sector.id == IdSector::FARM)
      for (const EntityState &entidad : sector.entities)
        if (esCofre(entidad))
          cofres.push_back(cofreGuardadoDe(entidad));
  return cofres;
}

AnimalGuardado animalGuardadoDe(const EntityState &entidad) {
  return AnimalGuardado{entidad.animal.type, entidad.position.x,
                        entidad.position.y, entidad.animal.is_ready};
}

std::vector<AnimalGuardado> animalesDe(const WorldState &estado) {
  std::vector<AnimalGuardado> animales;
  for (const SectorState &sector : estado.sectors)
    if (sector.id == IdSector::FARM)
      for (const EntityState &entidad : sector.entities)
        if (entidad.type == EntityTypes::ANIMAL)
          animales.push_back(animalGuardadoDe(entidad));
  return animales;
}

std::vector<CultivoGuardado> cultivosDe(const WorldState &estado) {
  std::vector<CultivoGuardado> cultivos;
  for (const SectorState &sector : estado.sectors)
    if (sector.id == IdSector::FARM)
      for (const EntityState &entidad : sector.entities)
        if (entidad.type == EntityTypes::CROP)
          cultivos.push_back(cultivoGuardadoDe(entidad));
  return cultivos;
}

using TablaPrecios = std::vector<std::pair<ClaveItem, int>>;

const TablaPrecios &tablaPrecios() {
  static const TablaPrecios tabla{
      {{ItemType::SEED, CropTypes::STRAWBERRY}, PRICE_SEED},
      {{ItemType::SEED, CropTypes::GREEN_ONION}, PRICE_SEED},
      {{ItemType::SEED, CropTypes::POTATO}, PRICE_SEED},
      {{ItemType::SEED, CropTypes::PUMPKIN}, PRICE_SEED},
      {{ItemType::CROP, CropTypes::STRAWBERRY}, PRICE_STRAWBERRY},
      {{ItemType::CROP, CropTypes::GREEN_ONION}, PRICE_GREEN_ONION},
      {{ItemType::CROP, CropTypes::POTATO}, PRICE_POTATO},
      {{ItemType::CROP, CropTypes::PUMPKIN}, PRICE_PUMPKIN},
      {{ItemType::MINERAL, MineralTypes::GOLD}, PRICE_GOLD},
      {{ItemType::MINERAL, MineralTypes::IRON}, PRICE_IRON},
      {{ItemType::MINERAL, MineralTypes::LAPIZLAZULI}, PRICE_LAPIZLAZULI},
      {{ItemType::MINERAL, MineralTypes::COAL}, PRICE_COAL},
      {{ItemType::ANIMAL_PRODUCT, AnimalType::COW}, PRICE_MILK},
      {{ItemType::ANIMAL_PRODUCT, AnimalType::CHICKEN}, PRICE_EGG},
      {{ItemType::ANIMAL, AnimalType::COW}, PRICE_COW},
      {{ItemType::ANIMAL, AnimalType::CHICKEN}, PRICE_CHICKEN},
      {{ItemType::FURNITURE, FurnitureType::CHEST}, PRICE_CHEST},
      {{ItemType::FURNITURE, FurnitureType::CHAIR}, PRICE_CHAIR},
      {{ItemType::FURNITURE, FurnitureType::TABLE}, PRICE_TABLE},
      {{ItemType::FURNITURE, FurnitureType::NIGHTSTAND}, PRICE_NIGHTSTAND},
      {{ItemType::FURNITURE, FurnitureType::FIREPLACE}, PRICE_FIREPLACE},
      {{ItemType::FURNITURE, FurnitureType::VASE}, PRICE_VASE},
      {{ItemType::FURNITURE, FurnitureType::SOFA}, PRICE_SOFA},
      {{ItemType::FURNITURE, FurnitureType::CRATE}, PRICE_CRATE},
      {{ItemType::FURNITURE, FurnitureType::BARREL}, PRICE_BARREL},
      {{ItemType::FURNITURE, FurnitureType::FLOWER_POT}, PRICE_FLOWER_POT},
      {{ItemType::FURNITURE, FurnitureType::SUNFLOWER}, PRICE_SUNFLOWER},
      {{ItemType::FURNITURE, FurnitureType::WELL}, PRICE_WELL}};
  return tabla;
}

int precioDe(const ClaveItem &clave) {
  for (const auto &[claveTabla, precio] : tablaPrecios())
    if (claveTabla == clave)
      return precio;
  throw std::logic_error(ERROR_ADAPTADOR_ITEM_SIN_PRECIO);
}

int subtipoEntero(const ItemSubtype &subtipo) {
  return std::visit([](auto valor) { return static_cast<int>(valor); },
                    subtipo);
}

std::unique_ptr<Item> crearItem(const ItemGuardado &item) {
  const ItemFactory fabrica;
  return fabrica.create(item.tipo, subtipoEntero(item.subtipo),
                        precioDe(ClaveItem{item.tipo, item.subtipo}),
                        item.calidad);
}

void vaciarInventario(Player &jugador) {
  Inventory &inventario = jugador.getInventory();
  const PlayerState estado = jugador.state();
  for (const ItemState &item : estado.inventory.items) {
    if (esGuardable(item)) {
      std::unique_ptr<Item> muestra = crearItem(itemGuardadoDe(item));
      inventario.remove(*muestra, inventario.countOf(*muestra));
    }
  }
}

void cargarItems(Inventory &inventario,
                 const std::vector<ItemGuardado> &items) {
  for (const ItemGuardado &item : items)
    for (int i = 0; i < item.cantidad; ++i)
      inventario.addItem(crearItem(item));
}

void restaurarCofre(Sector &granja, const CofreGuardado &guardado) {
  Position posicion(guardado.x, guardado.y);
  std::unique_ptr<Chest> cofre = std::make_unique<Chest>(posicion);
  cargarItems(cofre->getInventory(), guardado.inventario);
  std::unique_ptr<Entity> entidad = std::move(cofre);
  if (!granja.tryAddEntity(entidad, posicion))
    throw std::runtime_error(ERROR_ADAPTADOR_COFRE_OCUPADO);
}

void restaurarAnimal(World &mundo, Sector &granja,
                     const AnimalGuardado &guardado) {
  Position posicion(guardado.x, guardado.y);
  if (!mundo.spawnAnimal(IdSector::FARM, posicion, guardado.tipo))
    throw std::runtime_error(ERROR_ADAPTADOR_ANIMAL_OCUPADO);
  if (!guardado.listo)
    return;
  Entity *entidad = granja.getEntity(posicion);
  IGrowthCheat *animal = dynamic_cast<IGrowthCheat *>(entidad);
  if (animal != nullptr)
    animal->growthCheat();
}

} // namespace

PartidaGuardada extraerPartida(const World &mundo,
                               const PartidaGuardada &anterior) {
  const Sector *granja = mundo.getSector(IdSector::FARM);
  if (granja == nullptr)
    throw std::logic_error(ERROR_ADAPTADOR_SIN_GRANJA);

  const WorldState estado = mundo.state();
  PartidaGuardada partida = anterior;
  if (partida.nombre.empty())
    partida.nombre = estado.name;
  if (partida.codigo.empty())
    partida.codigo = estado.code;
  partida.dia = estado.dayNumber;
  for (const auto &[id, jugador] : mundo.getPlayers())
    actualizarJugador(partida.jugadores, jugadorGuardadoDe(*jugador));
  partida.multiplayer =
      partida.jugadores.size() >= MINIMO_JUGADORES_MULTIPLAYER;
  partida.granja.aradas = aradasDe(*granja);
  partida.granja.cultivos = cultivosDe(estado);
  partida.granja.cofres = cofresDe(estado);
  partida.granja.animales = animalesDe(estado);
  return partida;
}

void restaurarJugador(Player &jugador, const JugadorGuardado &guardado) {
  jugador.setLife(guardado.vida);
  jugador.setEnergy(guardado.energia);
  jugador.setCoins(guardado.oro);
  vaciarInventario(jugador);
  cargarItems(jugador.getInventory(), guardado.inventario);
}

void restaurarPartida(World &mundo, const PartidaGuardada &partida) {
  Sector *granja = mundo.getSector(IdSector::FARM);
  if (granja == nullptr)
    throw std::logic_error(ERROR_ADAPTADOR_SIN_GRANJA);
  mundo.setDayNumber(partida.dia);
  for (const CeldaGuardada &celda : partida.granja.aradas)
    granja->till(Position(celda.x, celda.y));
  for (const CofreGuardado &cofre : partida.granja.cofres)
  	restaurarCofre(*granja, cofre);
  for (const AnimalGuardado &animal : partida.granja.animales)
  	restaurarAnimal(mundo, *granja, animal);

}
