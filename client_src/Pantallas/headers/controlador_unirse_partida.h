#ifndef CONTROLADOR_UNIRSE_PARTIDA_H_
#define CONTROLADOR_UNIRSE_PARTIDA_H_

#include "controlador_pagina.h"
#include "dtos_pantallas.h"

class ControladorUnirsePartida : public ControladorPagina {
public:
  ControladorUnirsePartida(QWidget &ventana, Ui::Pantalla &ui,
                           NavegadorPaginas &navegador,
                           DatosPartida &datosPartida, ServicioLobby &servicio,
                           QObject *parent = nullptr);
  void reiniciarPagina() override;
  void actualizarEstadoBotonAvanzar() override;

private:
  DatosPartida &datosPartida;
  ServicioLobby &servicio;
  void avanzarACustomizarPersonaje();
};

#endif // CONTROLADOR_UNIRSE_PARTIDA_H_
