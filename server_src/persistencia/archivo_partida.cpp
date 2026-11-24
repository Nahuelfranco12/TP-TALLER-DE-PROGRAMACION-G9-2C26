#include "archivo_partida.h"

#include <cstddef>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <optional>
#include <stdexcept>
#include <string>
#include <system_error>
#include <toml++/toml.hpp>
#include <vector>
#include <algorithm>

#include "constantes_persistencia.h"
#include "ids_partida.h"
#include "lectura_toml.h"

namespace {
std::int64_t entero(std::size_t valor) {
  return static_cast<std::int64_t>(valor);
}

template <typename T>
toml::array arrayDe(const std::vector<T> &elementos,
                    toml::table (*convertir)(const T &)) {
  toml::array array;
  for (const T &elemento : elementos)
    array.push_back(convertir(elemento));
  return array;
}

toml::table tablaOutfit(const OutfitGuardado &outfit) {
  toml::table tabla{{CLAVE_PARTIDA_GORRO, outfit.gorro},
                    {CLAVE_PARTIDA_PELO, outfit.pelo},
                    {CLAVE_PARTIDA_REMERA, outfit.remera},
                    {CLAVE_PARTIDA_PANTALON, outfit.pantalon}};
  tabla.is_inline(true);
  return tabla;
}

toml::table tablaItem(const ItemGuardado &item) {
  toml::table tabla{
      {CLAVE_PARTIDA_TIPO, idDe(ClaveItem{item.tipo, item.subtipo})},
      {CLAVE_PARTIDA_CALIDAD, idDe(item.calidad)},
      {CLAVE_PARTIDA_CANTIDAD, item.cantidad}};
  tabla.is_inline(true);
  return tabla;
}

toml::table tablaCelda(const CeldaGuardada &celda) {
  toml::table tabla{{CLAVE_PARTIDA_X, entero(celda.x)},
                    {CLAVE_PARTIDA_Y, entero(celda.y)}};
  tabla.is_inline(true);
  return tabla;
}

toml::table tablaCultivo(const CultivoGuardado &cultivo) {
  return toml::table{
      {CLAVE_PARTIDA_TIPO, idDe(cultivo.tipo)},
      {CLAVE_PARTIDA_X, entero(cultivo.x)},
      {CLAVE_PARTIDA_Y, entero(cultivo.y)},
      {CLAVE_PARTIDA_CRECIMIENTO, entero(cultivo.crecimiento)},
      {CLAVE_PARTIDA_DESDE_RIEGO, entero(cultivo.desdeRiego)},
      {CLAVE_PARTIDA_CON_SED, entero(cultivo.conSed)},
      {CLAVE_PARTIDA_MADURO, entero(cultivo.maduro)},
      {CLAVE_PARTIDA_COSECHAS_EXTRA, entero(cultivo.cosechasExtra)},
      {CLAVE_PARTIDA_SUERTE, cultivo.suerte}};
}

toml::table tablaJugador(const JugadorGuardado &jugador) {
  return toml::table{
      {CLAVE_PARTIDA_NOMBRE, jugador.nombre},
      {CLAVE_PARTIDA_INDICE, entero(jugador.indiceCabania)},
      {CLAVE_PARTIDA_OUTFIT, tablaOutfit(jugador.outfit)},
      {CLAVE_PARTIDA_VIDA, jugador.vida},
      {CLAVE_PARTIDA_ENERGIA, jugador.energia},
      {CLAVE_PARTIDA_ORO, jugador.oro},
      {CLAVE_PARTIDA_INVENTARIO, arrayDe(jugador.inventario, tablaItem)}};
}

toml::table tablaGranja(const GranjaGuardada &granja) {
  return toml::table{
      {CLAVE_PARTIDA_ARADAS, arrayDe(granja.aradas, tablaCelda)},
      {CLAVE_PARTIDA_CULTIVOS, arrayDe(granja.cultivos, tablaCultivo)}};
}

void crearCarpeta(const std::filesystem::path &carpeta) {
  std::error_code error;
  std::filesystem::create_directories(carpeta, error);
  if (error)
    throw std::runtime_error(ERROR_PARTIDA_ESCRIBIR + carpeta.string());
}

template <typename T>
T leerId(const toml::table &tabla, const char *clave,
         const std::string &donde) {
  return elementoDesdeId<T>(leerValor<std::string>(tabla, clave, donde));
}

OutfitGuardado outfitDe(const toml::table &jugador, const std::string &donde) {
  const toml::table &tabla = leerSubtabla(jugador, CLAVE_PARTIDA_OUTFIT, donde);
  std::string lugar = rutaDelCampo(donde, CLAVE_PARTIDA_OUTFIT);
  return OutfitGuardado{
      leerEntero<int>(tabla, CLAVE_PARTIDA_GORRO, lugar),
      leerEntero<int>(tabla, CLAVE_PARTIDA_PELO, lugar),
      leerEntero<int>(tabla, CLAVE_PARTIDA_REMERA, lugar),
      leerEntero<int>(tabla, CLAVE_PARTIDA_PANTALON, lugar)};
}

ItemGuardado itemDe(const toml::table &tabla, const std::string &donde) {
  ClaveItem clave = leerId<ClaveItem>(tabla, CLAVE_PARTIDA_TIPO, donde);
  return ItemGuardado{
      clave.tipo, clave.subtipo,
      leerId<CropQuality>(tabla, CLAVE_PARTIDA_CALIDAD, donde),
      leerEntero<int>(tabla, CLAVE_PARTIDA_CANTIDAD, donde)};
}

CeldaGuardada celdaDe(const toml::table &tabla, const std::string &donde) {
  return CeldaGuardada{
      leerEntero<std::size_t>(tabla, CLAVE_PARTIDA_X, donde),
      leerEntero<std::size_t>(tabla, CLAVE_PARTIDA_Y, donde)};
}

CultivoGuardado cultivoDe(const toml::table &tabla, const std::string &donde) {
  return CultivoGuardado{
      leerId<CropTypes>(tabla, CLAVE_PARTIDA_TIPO, donde),
      leerEntero<std::size_t>(tabla, CLAVE_PARTIDA_X, donde),
      leerEntero<std::size_t>(tabla, CLAVE_PARTIDA_Y, donde),
      leerEntero<std::size_t>(tabla, CLAVE_PARTIDA_CRECIMIENTO, donde),
      leerEntero<std::size_t>(tabla, CLAVE_PARTIDA_DESDE_RIEGO, donde),
      leerEntero<std::size_t>(tabla, CLAVE_PARTIDA_CON_SED, donde),
      leerEntero<std::size_t>(tabla, CLAVE_PARTIDA_MADURO, donde),
      leerEntero<std::size_t>(tabla, CLAVE_PARTIDA_COSECHAS_EXTRA, donde),
      leerValor<double>(tabla, CLAVE_PARTIDA_SUERTE, donde)};
}

JugadorGuardado jugadorDe(const toml::table &tabla, const std::string &donde) {
  return JugadorGuardado{
      leerValor<std::string>(tabla, CLAVE_PARTIDA_NOMBRE, donde),
      leerEntero<std::size_t>(tabla, CLAVE_PARTIDA_INDICE, donde),
      outfitDe(tabla, donde),
      leerValor<double>(tabla, CLAVE_PARTIDA_VIDA, donde),
      leerValor<double>(tabla, CLAVE_PARTIDA_ENERGIA, donde),
      leerEntero<int>(tabla, CLAVE_PARTIDA_ORO, donde),
      leerLista(tabla, CLAVE_PARTIDA_INVENTARIO, donde, itemDe)};
}

GranjaGuardada granjaDe(const toml::table &raiz) {
  const toml::table &tabla = leerSubtabla(raiz, CLAVE_PARTIDA_GRANJA, {});
  return GranjaGuardada{
      leerLista(tabla, CLAVE_PARTIDA_ARADAS, CLAVE_PARTIDA_GRANJA, celdaDe),
      leerLista(tabla, CLAVE_PARTIDA_CULTIVOS, CLAVE_PARTIDA_GRANJA,
                cultivoDe)};
}
} // namespace

std::string carpetaDePartida(const std::string &codigo) {
  return (std::filesystem::path(RUTA_PARTIDAS) / codigo).string();
}

std::string rutaMapaGuardado(const std::string &carpeta) {
  return (std::filesystem::path(carpeta) / NOMBRE_ARCHIVO_MAPA).string();
}

void copiarMapa(const std::string &rutaMapa, const std::string &carpeta) {
  crearCarpeta(carpeta);
  std::error_code error;
  std::filesystem::copy_file(rutaMapa, rutaMapaGuardado(carpeta),
                             std::filesystem::copy_options::overwrite_existing,
                             error);
  if (error)
    throw std::runtime_error(ERROR_PARTIDA_COPIAR_MAPA + rutaMapa);
}

void escribirPartida(const PartidaGuardada &partida,
                     const std::string &carpeta) {
  toml::table raiz{
      {CLAVE_PARTIDA_VERSION, VERSION_ARCHIVO_PARTIDA},
      {CLAVE_PARTIDA_NOMBRE, partida.nombre},
      {CLAVE_PARTIDA_CODIGO, partida.codigo},
      {CLAVE_PARTIDA_DIA, entero(partida.dia)},
      {CLAVE_PARTIDA_MULTIPLAYER, partida.multiplayer},
      {CLAVE_PARTIDA_JUGADORES, arrayDe(partida.jugadores, tablaJugador)},
      {CLAVE_PARTIDA_GRANJA, tablaGranja(partida.granja)}};

  crearCarpeta(carpeta);
  std::filesystem::path destino =
      std::filesystem::path(carpeta) / NOMBRE_ARCHIVO_PARTIDA;
  std::filesystem::path temporal = destino;
  temporal += EXTENSION_ARCHIVO_TEMPORAL;

  std::ofstream archivo(temporal);
  if (!archivo)
    throw std::runtime_error(ERROR_PARTIDA_ESCRIBIR + temporal.string());
  archivo << raiz;
  archivo.close();
  if (!archivo)
    throw std::runtime_error(ERROR_PARTIDA_ESCRIBIR + temporal.string());

  std::error_code error;
  std::filesystem::rename(temporal, destino, error);
  if (error)
    throw std::runtime_error(ERROR_PARTIDA_ESCRIBIR + destino.string());
}

PartidaGuardada cargarPartida(const std::string &carpeta) {
  std::string ruta =
      (std::filesystem::path(carpeta) / NOMBRE_ARCHIVO_PARTIDA).string();
  toml::table raiz;
  try {
    raiz = toml::parse_file(ruta);
  } catch (const toml::parse_error &error) {
    throw std::runtime_error(ERROR_PARTIDA_LEER + ruta +
                             SEPARADOR_DETALLE_PARTIDA +
                             std::string(error.description()));
  }

  std::optional<std::int64_t> version =
      raiz[CLAVE_PARTIDA_VERSION].value<std::int64_t>();
  if (!version || *version != VERSION_ARCHIVO_PARTIDA)
    throw std::runtime_error(ERROR_PARTIDA_VERSION);

  return PartidaGuardada{
      leerValor<std::string>(raiz, CLAVE_PARTIDA_NOMBRE, {}),
      leerValor<std::string>(raiz, CLAVE_PARTIDA_CODIGO, {}),
      leerEntero<std::size_t>(raiz, CLAVE_PARTIDA_DIA, {}),
      leerValor<bool>(raiz, CLAVE_PARTIDA_MULTIPLAYER, {}),
      leerLista(raiz, CLAVE_PARTIDA_JUGADORES, {}, jugadorDe),
      granjaDe(raiz)};
}

std::vector<PartidaGuardada> listarPartidas() {
  std::vector<PartidaGuardada> partidas;
  std::error_code error;
  std::filesystem::directory_iterator carpetas(RUTA_PARTIDAS, error);
  if (error)
    return partidas;
  for (const std::filesystem::directory_entry &carpeta : carpetas) {
    if (!carpeta.is_directory(error))
      continue;
    try {
      partidas.push_back(cargarPartida(carpeta.path().string()));
    } catch (const std::runtime_error &) {
    }
  }
  std::ranges::sort(partidas, {}, &PartidaGuardada::nombre);
  return partidas;
}
