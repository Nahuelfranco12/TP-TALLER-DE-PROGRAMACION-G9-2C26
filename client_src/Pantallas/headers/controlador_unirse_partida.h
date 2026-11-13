#ifndef CONTROLADOR_UNIRSE_PARTIDA_H_
#define CONTROLADOR_UNIRSE_PARTIDA_H_

#include "controlador_pagina.h"
#include "dtos_pantallas.h"
#include <qwidget.h>

class ControladorUnirsePartida : public ControladorPagina {
public:
  ControladorUnirsePartida(QWidget &ventana, Ui::Pantalla &ui, Navegador &navegador,
                           DatosPartida &datosPartida,
                           QObject *parent = nullptr);
  void limpiarPagina() override;
  void actualizarBotonAvanzar() override;

private:
  DatosPartida &datosPartida;
};

#endif // CONTROLADOR_UNIRSE_PARTIDA_H_
