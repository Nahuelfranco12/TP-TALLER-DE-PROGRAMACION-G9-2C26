#ifndef ARCHIVO_PARTIDA_H_
#define ARCHIVO_PARTIDA_H_

#include <string>
#include <vector>
#include <string>

#include "partida_guardada.h"

std::vector<PartidaGuardada> listarPartidas();
std::string carpetaDePartida(const std::string &codigo);
std::string rutaMapaGuardado(const std::string &carpeta);
void copiarMapa(const std::string &rutaMapa, const std::string &carpeta);
void escribirPartida(const PartidaGuardada &partida,
                     const std::string &carpeta);
PartidaGuardada cargarPartida(const std::string &carpeta);

#endif // ARCHIVO_PARTIDA_H_
