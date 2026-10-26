#ifndef CONTROLADOR_NUEVA_PARTIDA_H
#define CONTROLADOR_NUEVA_PARTIDA_H

#include "controlador_pagina.h"
#include "lista_seleccionable.h"

class ControladorNuevaPartida : public ControladorPagina {
public:
  ControladorNuevaPartida(Ui::Pantalla &ui, Navegador &navegador,
                          QObject *parent = nullptr);

private:
  ListaSeleccionable *mundos;

  void cargarMundos();
  void reiniciar();
};

#endif // CONTROLADOR_NUEVA_PARTIDA_H
