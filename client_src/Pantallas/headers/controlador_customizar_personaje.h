#ifndef CONTROLADOR_CUSTOMIZAR_PERSONAJE_H
#define CONTROLADOR_CUSTOMIZAR_PERSONAJE_H

#include "constantes.h"
#include "controlador_pagina.h"
#include "datos_partida.h"
#include <QList>
#include <QPixmap>

struct CoordenadaSprite {
  int fila;
  int columna;
};

class ControladorCustomizarPersonaje : public ControladorPagina {
public:
  ControladorCustomizarPersonaje(Ui::Pantalla &ui, Navegador &navegador,
                                 DatosPartida &datosPartida,
                                 QObject *parent = nullptr);
  void limpiarPagina() override;
  void actualizarBotonAvanzar() override;

private:
  QList<CoordenadaSprite> opcionesPelo;
  QList<CoordenadaSprite> opcionesGorro;
  QList<CoordenadaSprite> opcionesPantalon;
  QList<CoordenadaSprite> opcionesRemera;

  int indicePelo = 0;
  int indiceGorro = 0;
  int indicePantalon = 0;
  int indiceRemera = 0;

  QPixmap hojaPelo;
  QPixmap hojaGorro;
  QPixmap hojaPantalon;
  QPixmap hojaRemera;
  QPixmap hojaBase;

  void inicializarListas();
  void conectarBotonesFlechas();
  void actualizarPrevisualizacion();
  void cambiarOpcion(int &indiceActual, int cantidadOpciones, int direccion);
  DatosPartida &datosPartida;
};

#endif // CONTROLADOR_CUSTOMIZAR_PERSONAJE_H
