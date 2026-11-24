#ifndef CONTROLADOR_NUEVA_PARTIDA_H_
#define CONTROLADOR_NUEVA_PARTIDA_H_

#include <QList>

#include "controlador_pagina.h"
#include "dtos_pantallas.h"
#include "lista_seleccionable.h"

class ControladorNuevaPartida : public ControladorPagina {
public:
  ControladorNuevaPartida(QWidget &ventana, Ui::Pantalla &ui,
                          NavegadorPaginas &navegador,
                          DatosPartida &datosPartida, ServicioLobby &servicio,
                          QObject *parent = nullptr);
  void reiniciarPagina() override;
  void actualizarEstadoBotonAvanzar() override;

private:
  ListaSeleccionable *listaMundos;
  QList<MundoMock> mundosDisponibles;
  DatosPartida &datosPartida;
  ServicioLobby &servicio;
  void pedirYMostrarMundos();
  bool mundosCargados = false;
};

#endif // CONTROLADOR_NUEVA_PARTIDA_H_
