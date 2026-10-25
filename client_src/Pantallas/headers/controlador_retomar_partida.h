#ifndef CONTROLADOR_RETOMAR_PARTIDA_H
#define CONTROLADOR_RETOMAR_PARTIDA_H

#include "controlador_pagina.h"
#include "lista_seleccionable.h"

class ControladorRetomarPartida : public ControladorPagina {
public:
  ControladorRetomarPartida(Ui::Pantalla &ui, Navegador &navegador,
                            QObject *parent = nullptr);

private:
  ListaSeleccionable *partidas;

  void cargarPartidas();
};

#endif // CONTROLADOR_RETOMAR_PARTIDA_H
