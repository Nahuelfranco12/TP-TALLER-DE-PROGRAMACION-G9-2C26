#include "validacion_mapas.h"

#include <algorithm>
#include <cstddef>
#include <string>
#include <utility>
#include <vector>

#include "constantes_mapa.h"
#include "elementos_mapa.h"
#include "mapa_editor.h"

namespace {
template <typename T> int contarObjetosDeTipo(const MapaZona<T> &zona, T tipo) {
  int cantidad = 0;
  for (const ObjetoColocado<T> &objeto : zona.objetos())
    if (objeto.tipo == tipo)
      ++cantidad;
  return cantidad;
}

int contarCabanias(const MapaZona<ElementosGranja> &granja) {
  int cantidad = 0;
  for (const ObjetoColocado<ElementosGranja> &objeto : granja.objetos())
    if (esCabania(objeto.tipo))
      ++cantidad;
  return cantidad;
}

std::string mensajeConLugar(const std::string &lugar,
                            const std::string &mensaje) {
  return lugar + VALIDACION_TEXTO_SEPARADOR + mensaje;
}

std::string mensajeFalta(const std::string &lugar, const char *nombre) {
  return mensajeConLugar(lugar, std::string(VALIDACION_TEXTO_FALTA) + nombre);
}

std::string mensajeSobra(const std::string &zona, const std::string &elemento) {
  return zona + VALIDACION_TEXTO_SEPARADOR + VALIDACION_TEXTO_SOBRA + elemento;
}

void validarGranja(const MapaZona<ElementosGranja> &granja,
                   std::vector<std::string> &errores) {
  int cabanias = contarCabanias(granja);
  if (cabanias < VALIDACION_CABANIAS_MINIMAS)
    errores.push_back(
        mensajeConLugar(VALIDACION_TEXTO_ZONA_GRANJA,
                        VALIDACION_TEXTO_CABANIAS_INICIO +
                            std::to_string(VALIDACION_CABANIAS_MINIMAS) +
                            VALIDACION_TEXTO_CABANIAS_FIN));
  if (contarObjetosDeTipo(granja, ElementosGranja::SalidaPueblo) == 0)
    errores.push_back(
        mensajeFalta(VALIDACION_TEXTO_ZONA_GRANJA, TEXTO_SALIDA_PUEBLO));
}

void validarPueblo(const MapaZona<ElementosPueblo> &pueblo,
                   std::vector<std::string> &errores) {
  static const std::vector<std::pair<ElementosPueblo, const char *>>
      obligatorios = {
          {ElementosPueblo::NpcMarnie, TEXTO_MARNIE},
          {ElementosPueblo::NpcClint, TEXTO_CLINT},
          {ElementosPueblo::NpcPierre, TEXTO_PIERRE},
          {ElementosPueblo::NpcRobin, TEXTO_ROBIN},
          {ElementosPueblo::CasaMarnie, TEXTO_CASA_MARNIE},
          {ElementosPueblo::CasaClint, TEXTO_CASA_CLINT},
          {ElementosPueblo::CasaPierre, TEXTO_CASA_PIERRE},
          {ElementosPueblo::CasaRobin, TEXTO_CASA_ROBIN},
          {ElementosPueblo::CentroComunitario, TEXTO_CENTRO_COMUNITARIO},
          {ElementosPueblo::SalidaGranja, TEXTO_SALIDA_GRANJA},
          {ElementosPueblo::EntradaMina, TEXTO_ENTRADA_MINA}};
  for (const auto &[tipo, nombre] : obligatorios)
    if (contarObjetosDeTipo(pueblo, tipo) == 0)
      errores.push_back(mensajeFalta(VALIDACION_TEXTO_ZONA_PUEBLO, nombre));
}

struct ReglaCaverna {
  ElementosCaverna tipo;
  const char *nombre;
  bool vaEnPrimerNivel;
  bool vaEnUltimoNivel;
  bool vaEnPared;
};

bool estaEnLaParedDeArriba(const MapaZona<ElementosCaverna> &nivel,
                           const ObjetoColocado<ElementosCaverna> &objeto) {
  TamanioEnCeldas tamanio = tamanioEnCeldasDe(objeto.tipo);
  bool enLaFilaDeArriba = objeto.y == 0;
  bool lejosDelExtremoIzquierdo = objeto.x > 0;
  bool lejosDelExtremoDerecho = objeto.x + tamanio.ancho < nivel.ancho();
  return enLaFilaDeArriba && lejosDelExtremoIzquierdo && lejosDelExtremoDerecho;
}

void validarCaverna(const std::vector<MapaZona<ElementosCaverna>> &niveles,
                    std::vector<std::string> &errores) {
  for (std::size_t i = 0; i < niveles.size(); ++i) {
    std::string nivel = std::string(VALIDACION_TEXTO_ZONA_CAVERNA) +
                        VALIDACION_TEXTO_NIVEL +
                        std::to_string(i + PRIMER_NIVEL_CAVERNA);
    bool esPrimero = i == 0, esUltimo = i + 1 == niveles.size();
    bool hayPozo = contarObjetosDeTipo(niveles[i], ElementosCaverna::Pozo) > 0;
    bool hayEscalera =
        contarObjetosDeTipo(niveles[i], ElementosCaverna::Escalera) > 0;

    if (contarObjetosDeTipo(niveles[i], ElementosCaverna::SalidaCaverna) == 0)
      errores.push_back(mensajeFalta(nivel, TEXTO_SALIDA_CAVERNA));

    if (!esUltimo && !hayPozo)
      errores.push_back(mensajeFalta(nivel, TEXTO_POZO));
    if (esUltimo && hayPozo)
      errores.push_back(mensajeSobra(nivel, TEXTO_POZO));

    if (!esPrimero && !hayEscalera)
      errores.push_back(mensajeFalta(nivel, TEXTO_ESCALERA));
    if (esPrimero && hayEscalera)
      errores.push_back(mensajeSobra(nivel, TEXTO_ESCALERA));

    for (const ObjetoColocado<ElementosCaverna> &objeto : niveles[i].objetos())
      if (objeto.tipo == ElementosCaverna::Escalera &&
          !estaEnLaParedDeArriba(niveles[i], objeto))
        errores.push_back(
            mensajeConLugar(nivel, VALIDACION_TEXTO_ESCALERA_PARED));



  }
}
} // namespace

std::vector<std::string> erroresParaExportar(const MapaEditor &mapa) {
  std::vector<std::string> errores;
  if (mapa.nombre.empty())
    errores.push_back(VALIDACION_TEXTO_ERROR_NOMBRE);
  validarGranja(mapa.granja, errores);
  validarPueblo(mapa.pueblo, errores);
  validarCaverna(mapa.nivelesCaverna, errores);
  return errores;
}
