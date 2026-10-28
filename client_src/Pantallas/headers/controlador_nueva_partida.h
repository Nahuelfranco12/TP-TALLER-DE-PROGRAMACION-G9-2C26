#ifndef CONTROLADOR_NUEVA_PARTIDA_H
#define CONTROLADOR_NUEVA_PARTIDA_H

#include "controlador_pagina.h"
#include "lista_seleccionable.h"

class ControladorNuevaPartida : public ControladorPagina {
public:
  ControladorNuevaPartida(Ui::Pantalla &ui, Navegador &navegador,
                          QObject *parent = nullptr);
  void reiniciar() override;
  void validarFormulario() override;

private:
  ListaSeleccionable *mundos;
  void cargarMundos();
};

#endif // CONTROLADOR_NUEVA_PARTIDA_H
