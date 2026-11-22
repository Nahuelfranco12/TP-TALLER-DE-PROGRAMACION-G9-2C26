#ifndef ARCHIVO_MAPA_H_
#define ARCHIVO_MAPA_H_

#include <string>

#include "mapa_editor.h"

void escribirMapaEnArchivo(const MapaEditor &mapa, const std::string &ruta);
MapaEditor cargarMapaDeArchivo(const std::string &ruta);

#endif // ARCHIVO_MAPA_H_
