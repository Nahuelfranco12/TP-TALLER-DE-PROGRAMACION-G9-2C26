#ifndef DATOS_EDITOR_H_
#define DATOS_EDITOR_H_

#include <QString>

enum class ModoEditor { Ninguno, Crear, Editar };

struct DatosEditor {
  ModoEditor modo = ModoEditor::Ninguno;
  QString rutaArchivo;
};

#endif  // DATOS_EDITOR_H_
