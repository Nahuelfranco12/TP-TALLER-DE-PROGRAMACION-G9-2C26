#include "adaptador_partida.h"

#include <algorithm>
#include <cstddef>
#include <stdexcept>
#include <utility>
#include <vector>

#include "constantes_persistencia.h"

namespace {
ItemSubtype subtipoDe(const ItemState &item) {
  switch (item.type) {
  case ItemType::MINERAL:
    return static_cast<MineralTypes>(item.subtype);
  case ItemType::SEED:
  case ItemType::CROP:
    return static_cast<CropTypes>(item.subtype);
  case ItemType::ANIMAL_PRODUCT:
    return static_cast<AnimalType>(item.subtype);
  case ItemType::DECORATION_PRODUCT:
    break;
  }
  throw std::logic_error(ERROR_ADAPTADOR_ITEM_SIN_SUBTIPO);
}

bool esGuardable(const ItemState &item) {
  return item.type != ItemType::DECORATION_PRODUCT;
}

ItemGuardado itemGuardadoDe(const ItemState &item) {
  return ItemGuardado{item.type, subtipoDe(item), item.quality, item.count};
}

OutfitGuardado outfitGuardadoDe(const PlayerOutfitState &outfit) {
  return OutfitGuardado{
      static_cast<int>(outfit.hat), static_cast<int>(outfit.hairs),
      static_cast<int>(outfit.tshirt), static_cast<int>(outfit.pants)};
}

JugadorGuardado jugadorGuardadoDe(const Player &jugador) {
  PlayerState estado = jugador.state();
  std::vector<ItemGuardado> inventario;
  for (const ItemState &item : estado.inventory.items){
  	if(esGuardable(item))
   		inventario.push_back(itemGuardadoDe(item));
  }
  return JugadorGuardado{jugador.getName(),
                         static_cast<std::size_t>(estado.id),
                         outfitGuardadoDe(estado.outfit),
                         estado.life,
                         estado.energy,
                         estado.coins,
                         std::move(inventario)};
}

void actualizarJugador(std::vector<JugadorGuardado> &jugadores,
                       JugadorGuardado jugador) {
  auto existente = std::ranges::find_if(
      jugadores, [&jugador](const JugadorGuardado &guardado) {
        return guardado.nombre == jugador.nombre;
      });
  if (existente == jugadores.end())
    jugadores.push_back(std::move(jugador));
  else
    *existente = std::move(jugador);
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

std::vector<CultivoGuardado> cultivosDe(const WorldState &estado) {
  std::vector<CultivoGuardado> cultivos;
  for (const SectorState &sector : estado.sectors)
    if (sector.id == IdSector::FARM)
      for (const EntityState &entidad : sector.entities)
        if (entidad.type == EntityTypes::CROP)
          cultivos.push_back(cultivoGuardadoDe(entidad));
  return cultivos;
}

} // namespace

PartidaGuardada extraerPartida(const World &mundo,
                               const PartidaGuardada &anterior) {
  const Sector *granja = mundo.getSector(IdSector::FARM);
  if (granja == nullptr)
    throw std::logic_error(ERROR_ADAPTADOR_SIN_GRANJA);

  const WorldState estado = mundo.state();
  PartidaGuardada partida = anterior;
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
  return partida;
}
