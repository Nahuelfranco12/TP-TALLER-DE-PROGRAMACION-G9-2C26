#ifndef CONTROLADOR_CUSTOMIZAR_PERSONAJE_H_
#define CONTROLADOR_CUSTOMIZAR_PERSONAJE_H_

#include "controlador_pagina.h"
#include "dibujar_personaje.h"
#include "dtos_pantallas.h"
#include "constantes_pantallas.h"

class ControladorCustomizarPersonaje : public ControladorPagina {
public:
  ControladorCustomizarPersonaje(QWidget &ventana, Ui::Pantalla &ui,
                                 NavegadorPaginas &navegador,
                                 DatosPartida &datosPartida,
                                 const DibujarPersonaje &dibujar,
                                 ServicioLobby &servicio,
                                 QObject *parent = nullptr);
  void reiniciarPagina() override;
  void actualizarEstadoBotonAvanzar() override;

private:
  int indicePelo = OPCION_POR_DEFECTO;
  int indiceGorro = OPCION_POR_DEFECTO;
  int indicePantalon = OPCION_POR_DEFECTO;
  int indiceRemera = OPCION_POR_DEFECTO;

  DatosPersonaje armarPersonajeElegido() const;

  void conectarFlechasDeTodasLasPrendas();
  void gorroAnterior();
  void gorroSiguiente();
  void peloAnterior();
  void peloSiguiente();
  void remeraAnterior();
  void remeraSiguiente();
  void pantalonAnterior();
  void pantalonSiguiente();
  void jugarConPersonajeElegido();
  void redibujarPrevisualizacionPersonaje();
  void cambiarOpcionPrenda(int &indiceActual,
                           const QList<CoordenadaSprite> &opciones,
                           int direccion);
  const DibujarPersonaje &dibujar;
  DatosPartida &datosPartida;
  ServicioLobby &servicio;
};

#endif // CONTROLADOR_CUSTOMIZAR_PERSONAJE_H_
