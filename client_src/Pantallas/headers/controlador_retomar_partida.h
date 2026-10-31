#ifndef CONTROLADOR_RETOMAR_PARTIDA_H
#define CONTROLADOR_RETOMAR_PARTIDA_H

#include "controlador_pagina.h"
#include "datos_partida.h"
#include "lista_seleccionable.h"

class ControladorRetomarPartida : public ControladorPagina {
public:
  ControladorRetomarPartida(Ui::Pantalla &ui, Navegador &navegador,
                            DatosPartida &datosPartida,
                            QObject *parent = nullptr);
  void limpiarPagina() override;
  void actualizarBotonAvanzar() override;

private:
  ListaSeleccionable *partidas;
  DatosPartida &datosPartida;
  void cargarPartidas();
};

#endif // CONTROLADOR_RETOMAR_PARTIDA_H
