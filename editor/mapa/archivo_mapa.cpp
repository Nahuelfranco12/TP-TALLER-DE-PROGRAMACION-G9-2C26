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
#include "ids_mapa.h"
#include "lectura_toml.h"

namespace {
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

Dimensiones leerDimensiones(const toml::table &tabla,
                            const std::string &donde) {
  Dimensiones dimensiones{leerEntero<int>(tabla, CLAVE_ANCHO, donde),
                          leerEntero<int>(tabla, CLAVE_ALTO, donde)};
  if (!dimensionesValidas(dimensiones))
    throw std::runtime_error(TEXTO_ERROR_DIMENSIONES + donde);
  return dimensiones;
}

template <typename T>
void cargarObjetos(const toml::table &tabla, MapaZona<T> &zona,
                   const std::string &donde) {
  const toml::array &objetos = leerArray(tabla, CLAVE_OBJETOS, donde);
  for (const toml::node &nodo : objetos) {
    const toml::table *objeto = nodo.as_table();
    if (objeto == nullptr)
      throw std::runtime_error(TEXTO_ERROR_CAMPO +
                               campo(donde, CLAVE_OBJETOS));
    std::string id = leerValor<std::string>(*objeto, CLAVE_TIPO, donde);
    T tipo = tipoDesdeId<T>(id);
    int x = leerEntero<int>(*objeto, CLAVE_X, donde);
    int y = leerEntero<int>(*objeto, CLAVE_Y, donde);
    if (!zona.colocar(tipo, x, y))
      throw std::runtime_error(TEXTO_ERROR_OBJETO + donde +
                               TEXTO_ABRE_ID_MAPA + id + TEXTO_CIERRA_ID_MAPA);
  }
}

template <typename T>
MapaZona<T> cargarZona(const toml::table &raiz, const char *clave,
                       Zona tipoZona) {
  const toml::table &tabla = leerTabla(raiz, clave, {});
  MapaZona<T> zona(leerDimensiones(tabla, clave), pisoBaseDe(tipoZona));
  cargarObjetos(tabla, zona, clave);
  return zona;
}

std::vector<MapaZona<ElementosCaverna>> cargarCaverna(const toml::table &raiz) {
  const toml::table &caverna = leerTabla(raiz, CLAVE_CAVERNA, {});
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
  archivo << raiz << FIN_ARCHIVO_MAPA;
  if (!archivo)
    throw std::runtime_error(TEXTO_ERROR_ESCRIBIR + ruta);
}

MapaEditor cargarMapa(const std::string &ruta) {
  toml::table raiz;
  try {
    raiz = toml::parse_file(ruta);
  } catch (const toml::parse_error &error) {
    throw std::runtime_error(TEXTO_ERROR_LEER + ruta + SEPARADOR_DETALLE_MAPA +
                             std::string(error.description()));
  }

  std::optional<std::int64_t> version =
      raiz[CLAVE_VERSION].value<std::int64_t>();
  if (!version || *version != VERSION_ARCHIVO_MAPA)
    throw std::runtime_error(TEXTO_ERROR_VERSION);

  std::string nombre = leerValor<std::string>(raiz, CLAVE_NOMBRE, {});

  return MapaEditor{
      nombre, cargarZona<ElementosGranja>(raiz, CLAVE_GRANJA, Zona::Granja),
      cargarCaverna(raiz),
      cargarZona<ElementosPueblo>(raiz, CLAVE_PUEBLO, Zona::Pueblo)};
}
