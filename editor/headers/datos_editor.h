#ifndef DATOS_EDITOR_H_
#define DATOS_EDITOR_H_

#include <QString>
#include <optional>

#include "mapa_editor.h"

enum class ModoEditor { Ninguno, Crear, Editar };

struct DatosEditor {
  ModoEditor modo = ModoEditor::Ninguno;
  QString rutaArchivo;
  std::optional<MapaEditor> mapa;
};

#endif  // DATOS_EDITOR_H_
