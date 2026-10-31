#ifndef CONTROLADOR_NUEVA_PARTIDA_H
#define CONTROLADOR_NUEVA_PARTIDA_H

#include "controlador_pagina.h"
#include "datos_partida.h"
#include "lista_seleccionable.h"

class ControladorNuevaPartida : public ControladorPagina {
public:
  ControladorNuevaPartida(Ui::Pantalla &ui, Navegador &navegador,
                          DatosPartida &datosPartida, ServicioLobby &servicio,
                          QObject *parent = nullptr);
  void limpiarPagina() override;
  void actualizarBotonAvanzar() override;

private:
  ListaSeleccionable *mundos;
  DatosPartida &datosPartida;
  ServicioLobby &servicio;
  void cargarMundos();
};

#endif // CONTROLADOR_NUEVA_PARTIDA_H
