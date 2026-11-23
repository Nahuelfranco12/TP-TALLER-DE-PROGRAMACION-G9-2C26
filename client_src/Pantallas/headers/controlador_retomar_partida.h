#ifndef CONTROLADOR_RETOMAR_PARTIDA_H_
#define CONTROLADOR_RETOMAR_PARTIDA_H_

#include "controlador_pagina.h"
#include "dibujar_personaje.h"
#include "dtos_pantallas.h"
#include "lista_seleccionable.h"

class ControladorRetomarPartida : public ControladorPagina {
public:
  ControladorRetomarPartida(QWidget &ventana, Ui::Pantalla &ui,
                            Navegador &navegador, DatosPartida &datosPartida,
                            const DibujarPersonaje &dibujante,
                            ServicioLobby &servicio, QObject *parent = nullptr);
  void limpiarPagina() override;
  void actualizarBotonAvanzar() override;

private:
  ListaSeleccionable *partidas;
  DatosPartida &datosPartida;
  const DibujarPersonaje &dibujante;
  ServicioLobby &servicio;
  void cargarPartidas();
};

#endif // CONTROLADOR_RETOMAR_PARTIDA_H_
