#ifndef CONTROLADOR_CUSTOMIZAR_PERSONAJE_H
#define CONTROLADOR_CUSTOMIZAR_PERSONAJE_H

#include "controlador_pagina.h"
#include <QList>
#include <QPixmap>

struct CoordenadaSprite {
  int fila;
  int columna;
};

class ControladorCustomizarPersonaje : public ControladorPagina {
public:
  ControladorCustomizarPersonaje(Ui::Pantalla &ui, Navegador &navegador,
                                 QObject *parent = nullptr);
  void reiniciar() override;
  void validarFormulario() override;

private:
#define ANCHO_GORRO 20
#define ALTO_GORRO 20
#define ANCHO_PELO 16
#define ALTO_PELO 32
#define ANCHO_REMERA 8
#define ALTO_REMERA 8
#define ANCHO_PANTALON 16
#define ALTO_PANTALON 32

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
};

#endif // CONTROLADOR_CUSTOMIZAR_PERSONAJE_H
