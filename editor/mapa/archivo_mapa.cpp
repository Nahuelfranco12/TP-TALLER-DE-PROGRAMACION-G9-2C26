#include "archivo_mapa.h"

#include <fstream>
#include <stdexcept>
#include <string>
#include <toml++/toml.hpp>
#include <utility>
#include <vector>

#include "constantes.h"
#include "elementos_mapa.h"

namespace {
template <typename T> using TablaIds = std::vector<std::pair<T, const char *>>;

const TablaIds<ElementosGranja> &tablaIds(ElementosGranja) {
  static const TablaIds<ElementosGranja> tabla = {
      {ElementosGranja::Cabania1, "Cabania1"},
      {ElementosGranja::Cabania2, "Cabania2"},
      {ElementosGranja::Cabania3, "Cabania3"},
      {ElementosGranja::Cabania4, "Cabania4"},
      {ElementosGranja::Cabania5, "Cabania5"},
      {ElementosGranja::SalidaPueblo, "SalidaPueblo"},
      {ElementosGranja::Arbol1, "Arbol1"},
      {ElementosGranja::Arbol2, "Arbol2"},
      {ElementosGranja::Agua, "Agua"},
      {ElementosGranja::Piedra, "Piedra"},
      {ElementosGranja::PiedraGrisGrande, "PiedraGrisGrande"},
      {ElementosGranja::PiedraGris, "PiedraGris"},
      {ElementosGranja::ArbustoRedondo, "ArbustoRedondo"},
      {ElementosGranja::ArbustoGrande, "ArbustoGrande"},
      {ElementosGranja::TroncoTirado, "TroncoTirado"},
      {ElementosGranja::TroncoPartido, "Tocon"},
      {ElementosGranja::BuzonRojo, "BuzonRojo"},
      {ElementosGranja::CartelVacio, "CartelVacio"}};
  return tabla;
}

const TablaIds<ElementosCaverna> &tablaIds(ElementosCaverna) {
  static const TablaIds<ElementosCaverna> tabla = {
      {ElementosCaverna::Escalera, "Escalera"},
      {ElementosCaverna::SalidaCaverna, "SalidaCaverna"},
      {ElementosCaverna::Barril, "Barril"},
      {ElementosCaverna::Calavera, "Calavera"},
      {ElementosCaverna::Hueso, "Hueso"},
      {ElementosCaverna::Escombros, "Escombros"},
      {ElementosCaverna::Antorchas, "Antorchas"},
      {ElementosCaverna::Candelabro, "Candelabro"},
      {ElementosCaverna::Escudo, "Escudo"}};
  return tabla;
}

const TablaIds<ElementosPueblo> &tablaIds(ElementosPueblo) {
  static const TablaIds<ElementosPueblo> tabla = {
      {ElementosPueblo::NpcMarnie, "NpcMarnie"},
      {ElementosPueblo::NpcClint, "NpcClint"},
      {ElementosPueblo::NpcPierre, "NpcPierre"},
      {ElementosPueblo::NpcRobin, "NpcRobin"},
      {ElementosPueblo::CasaMarnie, "CasaMarnie"},
      {ElementosPueblo::CasaClint, "CasaClint"},
      {ElementosPueblo::CasaPierre, "CasaPierre"},
      {ElementosPueblo::CasaRobin, "CasaRobin"},
      {ElementosPueblo::CentroComunitario, "CentroComunitario"},
      {ElementosPueblo::SalidaGranja, "SalidaGranja"},
      {ElementosPueblo::EntradaMina, "EntradaMina"},
      {ElementosPueblo::FarolNaranja, "FarolNaranja"},
      {ElementosPueblo::FarolAzul, "FarolAzul"},
      {ElementosPueblo::BancoMadera, "BancoMadera"},
      {ElementosPueblo::BuzonGris, "BuzonGris"},
      {ElementosPueblo::BuzonAzul, "BuzonAzul"}};
  return tabla;
}

template <typename T> const char *idDe(T tipo) {
  for (const auto &[elemento, id] : tablaIds(T{}))
    if (elemento == tipo)
      return id;
  throw std::logic_error(TEXTO_ERROR_SIN_ID);
}

template <typename T> toml::array objetosDe(const MapaZona<T> &zona) {
  toml::array objetos;
  for (const auto &objeto : zona.objetos()) {
    toml::table entrada{{CLAVE_TIPO, idDe(objeto.tipo)},
                        {CLAVE_X, objeto.x},
                        {CLAVE_Y, objeto.y}};
    entrada.is_inline(true);
    objetos.push_back(std::move(entrada));
  }
  return objetos;
}

template <typename T> toml::table tablaDe(const MapaZona<T> &zona) {
  return toml::table{{CLAVE_ANCHO, zona.ancho()},
                     {CLAVE_ALTO, zona.alto()},
                     {CLAVE_OBJETOS, objetosDe(zona)}};
}

toml::table tablaCaverna(
    const std::vector<MapaZona<ElementosCaverna>> &niveles) {
  toml::table caverna{{CLAVE_ANCHO, niveles.front().ancho()},
                      {CLAVE_ALTO, niveles.front().alto()}};
  toml::array listaNiveles;
  for (const auto &nivel : niveles)
    listaNiveles.push_back(toml::table{{CLAVE_OBJETOS, objetosDe(nivel)}});
  caverna.insert(CLAVE_NIVELES, std::move(listaNiveles));
  return caverna;
}
} // namespace

void escribirMapa(const MapaEditor &mapa, const std::string &ruta) {
  toml::table raiz{{CLAVE_VERSION, VERSION_ARCHIVO_MAPA},
                   {CLAVE_NOMBRE, mapa.nombre},
                   {CLAVE_GRANJA, tablaDe(mapa.granja)},
                   {CLAVE_PUEBLO, tablaDe(mapa.pueblo)},
                   {CLAVE_CAVERNA, tablaCaverna(mapa.nivelesCaverna)}};

  std::ofstream archivo(ruta);
  if (!archivo)
    throw std::runtime_error(TEXTO_ERROR_ESCRIBIR + ruta);
  archivo << raiz << '\n';
  if (!archivo)
    throw std::runtime_error(TEXTO_ERROR_ESCRIBIR + ruta);
}
