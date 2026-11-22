#ifndef CONTROLADOR_INICIO_EDITOR_H_
#define CONTROLADOR_INICIO_EDITOR_H_

#include "controlador_pagina_editor.h"
#include "datos_editor.h"
#include <QWidget>

class ControladorInicioEditor : public ControladorPaginaEditor {
public:
  ControladorInicioEditor(QWidget &ventana, Ui::VentanaEditor &ui,
                          NavegadorPaginas &navegador, DatosEditor &datos,
                          QObject *parent = nullptr);

private:
  DatosEditor &datos;
  void crearMapa();
  void cargarMapaExistente();
};

#endif // CONTROLADOR_INICIO_EDITOR_H_
