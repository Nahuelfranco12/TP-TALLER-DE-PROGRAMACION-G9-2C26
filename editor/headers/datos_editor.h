#ifndef DATOS_EDITOR_H_
#define DATOS_EDITOR_H_

#include <QString>

#include "mapa_editor.h"

struct DatosEditor {
  QString rutaArchivo;
  MapaEditor mapa = crearMapaVacio();
};

#endif // DATOS_EDITOR_H_
