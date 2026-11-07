#ifndef CONTROLADOR_INICIO_EDITOR_H_
#define CONTROLADOR_INICIO_EDITOR_H_

#include "controlador_pagina_editor.h"
#include "datos_editor.h"

class ControladorInicioEditor : public ControladorPaginaEditor {
 public:
  ControladorInicioEditor(Ui::VentanaEditor &ui, Navegador &navegador,
                          DatosEditor &datos, QObject *parent = nullptr);
  void limpiarPagina() override;

 private:
  DatosEditor &datos;
  void crearMapa();
  void editarMapa();
};

#endif  // CONTROLADOR_INICIO_EDITOR_H_
