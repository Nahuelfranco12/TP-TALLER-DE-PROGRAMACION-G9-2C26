#include "archivo_mapa.h"

#include <cstdint>
#include <fstream>
#include <optional>
#include <stdexcept>
#include <string>
#include <toml++/toml.hpp>
#include <utility>
#include <vector>

#include "constantes_mapa.h"

namespace {
template <typename T> using TablaIds = std::vector<std::pair<T, const char *>>;

const TablaIds<ElementosGranja> &tablaIds(ElementosGranja) {
  static const TablaIds<ElementosGranja> tabla = {
      {ElementosGranja::Cabania1, ID_CABANIA1},
      {ElementosGranja::Cabania2, ID_CABANIA2},
      {ElementosGranja::Cabania3, ID_CABANIA3},
      {ElementosGranja::Cabania4, ID_CABANIA4},
      {ElementosGranja::Cabania5, ID_CABANIA5},
      {ElementosGranja::SalidaPueblo, ID_SALIDA_PUEBLO},
      {ElementosGranja::Arbol1, ID_ARBOL1},
      {ElementosGranja::Arbol2, ID_ARBOL2},
      {ElementosGranja::Agua, ID_AGUA},
      {ElementosGranja::Piedra, ID_PIEDRA},
      {ElementosGranja::PiedraGrisGrande, ID_PIEDRA_GRIS_GRANDE},
      {ElementosGranja::PiedraGris, ID_PIEDRA_GRIS},
      {ElementosGranja::ArbustoRedondo, ID_ARBUSTO_REDONDO},
      {ElementosGranja::ArbustoGrande, ID_ARBUSTO_GRANDE},
      {ElementosGranja::TroncoCaido, ID_TRONCO_CAIDO},
      {ElementosGranja::Tocon, ID_TOCON},
      {ElementosGranja::BuzonRojo, ID_BUZON_ROJO},
      {ElementosGranja::CartelVacio, ID_CARTEL_VACIO}};
  return tabla;
}

const TablaIds<ElementosCaverna> &tablaIds(ElementosCaverna) {
  static const TablaIds<ElementosCaverna> tabla = {
      {ElementosCaverna::Escalera, ID_ESCALERA},
      {ElementosCaverna::SalidaCaverna, ID_SALIDA_CAVERNA},
      {ElementosCaverna::Barril, ID_BARRIL},
      {ElementosCaverna::Calavera, ID_CALAVERA},
      {ElementosCaverna::Hueso, ID_HUESO},
      {ElementosCaverna::Escombros, ID_ESCOMBROS},
      {ElementosCaverna::Antorcha, ID_ANTORCHA},
      {ElementosCaverna::Candelabro, ID_CANDELABRO},
      {ElementosCaverna::Candelabro, ID_CANDELABRO},
      {ElementosCaverna::Escudo, ID_ESCUDO},
      {ElementosCaverna::Pozo, ID_POZO}};
  return tabla;
}

const TablaIds<ElementosPueblo> &tablaIds(ElementosPueblo) {
  static const TablaIds<ElementosPueblo> tabla = {
      {ElementosPueblo::NpcMarnie, ID_NPC_MARNIE},
      {ElementosPueblo::NpcClint, ID_NPC_CLINT},
      {ElementosPueblo::NpcPierre, ID_NPC_PIERRE},
      {ElementosPueblo::NpcRobin, ID_NPC_ROBIN},
      {ElementosPueblo::CasaMarnie, ID_CASA_MARNIE},
      {ElementosPueblo::CasaClint, ID_CASA_CLINT},
      {ElementosPueblo::CasaPierre, ID_CASA_PIERRE},
      {ElementosPueblo::CasaRobin, ID_CASA_ROBIN},
      {ElementosPueblo::CentroComunitario, ID_CENTRO_COMUNITARIO},
      {ElementosPueblo::SalidaGranja, ID_SALIDA_GRANJA},
      {ElementosPueblo::EntradaMina, ID_ENTRADA_MINA},
      {ElementosPueblo::FarolNaranja, ID_FAROL_NARANJA},
      {ElementosPueblo::FarolAzul, ID_FAROL_AZUL},
      {ElementosPueblo::BancoMadera, ID_BANCO_MADERA},
      {ElementosPueblo::BuzonGris, ID_BUZON_GRIS},
      {ElementosPueblo::BuzonAzul, ID_BUZON_AZUL}};
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

toml::table
tablaCaverna(const std::vector<MapaZona<ElementosCaverna>> &niveles) {
  toml::table caverna{{CLAVE_ANCHO, niveles.front().ancho()},
                      {CLAVE_ALTO, niveles.front().alto()}};
  toml::array listaNiveles;
  for (const auto &nivel : niveles)
    listaNiveles.push_back(toml::table{{CLAVE_OBJETOS, objetosDe(nivel)}});
  caverna.insert(CLAVE_NIVELES, std::move(listaNiveles));
  return caverna;
}

template <typename T> T tipoDesdeId(const std::string &id) {
  for (const auto &[elemento, texto] : tablaIds(T{}))
    if (id == texto)
      return elemento;
  throw std::runtime_error(TEXTO_ERROR_TIPO + id);
}

int leerEntero(const toml::table &tabla, const char *clave,
               const std::string &donde) {
  std::optional<std::int64_t> valor = tabla[clave].value<std::int64_t>();
  if (!valor)
    throw std::runtime_error(TEXTO_ERROR_CAMPO + donde + "." + clave);
  if (!std::in_range<int>(*valor))
    throw std::runtime_error(TEXTO_ERROR_RANGO + donde + "." + clave);
  return static_cast<int>(*valor);
}

const toml::table &leerTabla(const toml::table &tabla, const char *clave) {
  const toml::table *subtabla = tabla[clave].as_table();
  if (subtabla == nullptr)
    throw std::runtime_error(TEXTO_ERROR_CAMPO + std::string(clave));
  return *subtabla;
}

Dimensiones leerDimensiones(const toml::table &tabla,
                            const std::string &donde) {
  Dimensiones dimensiones{leerEntero(tabla, CLAVE_ANCHO, donde),
                          leerEntero(tabla, CLAVE_ALTO, donde)};
  if (!dimensionesValidas(dimensiones))
    throw std::runtime_error(TEXTO_ERROR_DIMENSIONES + donde);
  return dimensiones;
}

template <typename T>
void cargarObjetos(const toml::table &tabla, MapaZona<T> &zona,
                   const std::string &donde) {
  const toml::array *objetos = tabla[CLAVE_OBJETOS].as_array();
  if (objetos == nullptr)
    throw std::runtime_error(TEXTO_ERROR_CAMPO + donde + "." + CLAVE_OBJETOS);
  for (const toml::node &nodo : *objetos) {
    const toml::table *objeto = nodo.as_table();
    if (objeto == nullptr)
      throw std::runtime_error(TEXTO_ERROR_CAMPO + donde + "." + CLAVE_OBJETOS);
    std::optional<std::string> id = (*objeto)[CLAVE_TIPO].value<std::string>();
    if (!id)
      throw std::runtime_error(TEXTO_ERROR_CAMPO + donde + "." + CLAVE_TIPO);
    T tipo = tipoDesdeId<T>(*id);
    int x = leerEntero(*objeto, CLAVE_X, donde);
    int y = leerEntero(*objeto, CLAVE_Y, donde);
    if (!zona.colocar(tipo, x, y))
      throw std::runtime_error(TEXTO_ERROR_OBJETO + donde + " (" + *id + ")");
  }
}

template <typename T>
MapaZona<T> cargarZona(const toml::table &raiz, const char *clave,
                       Zona tipoZona) {
  const toml::table &tabla = leerTabla(raiz, clave);
  MapaZona<T> zona(leerDimensiones(tabla, clave), pisoBaseDe(tipoZona));
  cargarObjetos(tabla, zona, clave);
  return zona;
}

std::vector<MapaZona<ElementosCaverna>> cargarCaverna(const toml::table &raiz) {
  const toml::table &caverna = leerTabla(raiz, CLAVE_CAVERNA);
  Dimensiones dimensiones = leerDimensiones(caverna, CLAVE_CAVERNA);
  const toml::array *niveles = caverna[CLAVE_NIVELES].as_array();
  if (niveles == nullptr || niveles->size() != CANTIDAD_NIVELES_CAVERNA)
    throw std::runtime_error(TEXTO_ERROR_NIVELES);

  std::vector<MapaZona<ElementosCaverna>> resultado;
  int numero = PRIMER_NIVEL_CAVERNA;
  for (const toml::node &nodo : *niveles) {
    std::string donde = std::string(CLAVE_CAVERNA) + TEXTO_NIVEL_ARCHIVO +
                        std::to_string(numero);
    const toml::table *tablaNivel = nodo.as_table();
    if (tablaNivel == nullptr)
      throw std::runtime_error(TEXTO_ERROR_CAMPO + donde);
    MapaZona<ElementosCaverna> nivel = crearNivelCaverna(dimensiones);
    cargarObjetos(*tablaNivel, nivel, donde);
    resultado.push_back(std::move(nivel));
    ++numero;
  }
  return resultado;
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

MapaEditor cargarMapa(const std::string &ruta) {
  toml::table raiz;
  try {
    raiz = toml::parse_file(ruta);
  } catch (const toml::parse_error &error) {
    throw std::runtime_error(TEXTO_ERROR_LEER + ruta + "\n" +
                             std::string(error.description()));
  }

  std::optional<std::int64_t> version =
      raiz[CLAVE_VERSION].value<std::int64_t>();
  if (!version || *version != VERSION_ARCHIVO_MAPA)
    throw std::runtime_error(TEXTO_ERROR_VERSION);

  std::optional<std::string> nombre = raiz[CLAVE_NOMBRE].value<std::string>();
  if (!nombre)
    throw std::runtime_error(TEXTO_ERROR_CAMPO + std::string(CLAVE_NOMBRE));

  return MapaEditor{
      *nombre, cargarZona<ElementosGranja>(raiz, CLAVE_GRANJA, Zona::Granja),
      cargarCaverna(raiz),
      cargarZona<ElementosPueblo>(raiz, CLAVE_PUEBLO, Zona::Pueblo)};
}
