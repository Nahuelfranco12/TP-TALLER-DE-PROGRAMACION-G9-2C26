#ifndef CONTROLADOR_MAPAS_H_
#define CONTROLADOR_MAPAS_H_

#include <vector>

#include "controlador_pagina_editor.h"
#include "datos_editor.h"
#include "editor_dtos.h"

class QWidget;

class ControladorMapas : public ControladorPaginaEditor {
 public:
  ControladorMapas(Ui::VentanaEditor &ui, Navegador &navegador,
                   DatosEditor &datos, QObject *parent = nullptr);
  void limpiarPagina() override;

 private:
  DatosEditor &datos;

  Zona zonaDe(QWidget *pestania) const;
  void cargarPaleta(Zona zona);
  template <typename T>
  void agregarAPaleta(const std::vector<InfoElemento<T>> &elementos);
};

#endif  // CONTROLADOR_MAPAS_H_
