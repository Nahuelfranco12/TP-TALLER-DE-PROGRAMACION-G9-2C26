#ifndef CONTROLADOR_RETOMAR_PARTIDA_H
#define CONTROLADOR_RETOMAR_PARTIDA_H

#include "controlador_pagina.h"
#include "datos_partida.h"
#include "dibujar_personaje.h"
#include "lista_seleccionable.h"

class ControladorRetomarPartida : public ControladorPagina {
public:
  ControladorRetomarPartida(Ui::Pantalla &ui, Navegador &navegador,
                            DatosPartida &datosPartida,
                            const DibujarPersonaje &dibujante,
                            QObject *parent = nullptr);
  void limpiarPagina() override;
  void actualizarBotonAvanzar() override;

private:
  ListaSeleccionable *partidas;
  DatosPartida &datosPartida;
  const DibujarPersonaje &dibujante;
  void cargarPartidas();
};

#endif // CONTROLADOR_RETOMAR_PARTIDA_H
