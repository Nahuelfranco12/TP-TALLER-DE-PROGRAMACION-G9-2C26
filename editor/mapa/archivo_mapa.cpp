#include "archivo_mapa.h"

#include <fstream>
#include <stdexcept>
#include <string>
#include <toml++/toml.hpp>
#include <utility>
#include <vector>
#include <cstdint>
#include <optional>

#include "constantes_mapa.h"

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
      {ElementosGranja::TroncoCaido, "TroncoCaido"},
      {ElementosGranja::Tocon, "Tocon"},
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
      {ElementosCaverna::Antorcha, "Antorcha"},
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

// Elemento que corresponde a un texto del archivo. Lanza si no existe.
template <typename T> T tipoDesdeId(const std::string &id) {
  for (const auto &[elemento, texto] : tablaIds(T{}))
    if (id == texto)
      return elemento;
  throw std::runtime_error(TEXTO_ERROR_TIPO + id);
}

// Lee un entero obligatorio de una tabla. `donde` es para el mensaje de error.
int leerEntero(const toml::table &tabla, const char *clave,
               const std::string &donde) {
  std::optional<std::int64_t> valor = tabla[clave].value<std::int64_t>();
  if (!valor)
    throw std::runtime_error(TEXTO_ERROR_CAMPO + donde + "." + clave);
  return static_cast<int>(*valor);
}

// Lee una subtabla obligatoria (por ejemplo, [granja]).
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

// Coloca en la zona los objetos de la lista. Usa colocar(), así que se
// vuelven a chequear las reglas: que entren y que no se pisen.
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
                       Terreno pisoBase) {
  const toml::table &tabla = leerTabla(raiz, clave);
  MapaZona<T> zona(leerDimensiones(tabla, clave), pisoBase);
  cargarObjetos(tabla, zona, clave);
  return zona;
}

std::vector<MapaZona<ElementosCaverna>> cargarCaverna(
    const toml::table &raiz) {
  const toml::table &caverna = leerTabla(raiz, CLAVE_CAVERNA);
  Dimensiones dimensiones = leerDimensiones(caverna, CLAVE_CAVERNA);
  const toml::array *niveles = caverna[CLAVE_NIVELES].as_array();
  if (niveles == nullptr || niveles->size() != CANTIDAD_NIVELES_CAVERNA)
    throw std::runtime_error(TEXTO_ERROR_NIVELES);

  std::vector<MapaZona<ElementosCaverna>> resultado;
  int numero = PRIMER_NIVEL_CAVERNA;
  for (const toml::node &nodo : *niveles) {
    std::string donde =
        std::string(CLAVE_CAVERNA) + TEXTO_NIVEL_ARCHIVO + std::to_string(numero);
    const toml::table *tablaNivel = nodo.as_table();
    if (tablaNivel == nullptr)
      throw std::runtime_error(TEXTO_ERROR_CAMPO + donde);
    MapaZona<ElementosCaverna> nivel(dimensiones, Terreno::PisoCaverna);
    pintarBorde(nivel, Terreno::Pared);
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

  std::optional<std::int64_t> version = raiz[CLAVE_VERSION].value<std::int64_t>();
  if (!version || *version != VERSION_ARCHIVO_MAPA)
    throw std::runtime_error(TEXTO_ERROR_VERSION);

  std::optional<std::string> nombre = raiz[CLAVE_NOMBRE].value<std::string>();
  if (!nombre)
    throw std::runtime_error(TEXTO_ERROR_CAMPO + std::string(CLAVE_NOMBRE));

  return MapaEditor{
      *nombre,
      cargarZona<ElementosGranja>(raiz, CLAVE_GRANJA, Terreno::Pasto),
      cargarCaverna(raiz),
      cargarZona<ElementosPueblo>(raiz, CLAVE_PUEBLO, Terreno::PisoPueblo)};
}
