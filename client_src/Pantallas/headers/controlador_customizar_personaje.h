#ifndef CONTROLADOR_CUSTOMIZAR_PERSONAJE_H
#define CONTROLADOR_CUSTOMIZAR_PERSONAJE_H

#include "controlador_pagina.h"
#include "dibujar_personaje.h"
#include "dtos_pantallas.h"
#include <QList>

class ControladorCustomizarPersonaje : public ControladorPagina {
public:
  ControladorCustomizarPersonaje(Ui::Pantalla &ui, Navegador &navegador,
                                 DatosPartida &datosPartida,
                                 const DibujarPersonaje &dibujar,
                                 ServicioLobby &servicio,
                                 QObject *parent = nullptr);
  void limpiarPagina() override;
  void actualizarBotonAvanzar() override;

private:
  int indicePelo = 0;
  int indiceGorro = 0;
  int indicePantalon = 0;
  int indiceRemera = 0;

  DatosPersonaje personajeElegido() const;

  // void inicializarListas();
  void conectarBotonesFlechas();
  void actualizarPrevisualizacion();
  void cambiarOpcion(int &indiceActual, int cantidadOpciones, int direccion);
  const DibujarPersonaje &dibujar;
  DatosPartida &datosPartida;
  ServicioLobby &servicio;
};

#endif // CONTROLADOR_CUSTOMIZAR_PERSONAJE_H
