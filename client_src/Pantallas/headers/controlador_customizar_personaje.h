#ifndef CONTROLADOR_CUSTOMIZAR_PERSONAJE_H_
#define CONTROLADOR_CUSTOMIZAR_PERSONAJE_H_

#include "controlador_pagina.h"
#include "dibujar_personaje.h"
#include "dtos_pantallas.h"

class ControladorCustomizarPersonaje : public ControladorPagina {
public:
	ControladorCustomizarPersonaje(QWidget &ventana, Ui::Pantalla &ui,
                                 Navegador &navegador,
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

  void conectarBotonesFlechas();
  void actualizarPrevisualizacion();
  void cambiarOpcion(int &indiceActual, int cantidadOpciones, int direccion);
  const DibujarPersonaje &dibujar;
  DatosPartida &datosPartida;
  ServicioLobby &servicio;
};

#endif // CONTROLADOR_CUSTOMIZAR_PERSONAJE_H_
